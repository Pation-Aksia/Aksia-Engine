#include "AWindow.h"

#include "AMath.h"
#include "GLContext.h"
#include "Texture2D.h"

#include <iostream>
#include <string>

#include <sys/ipc.h>
#include <sys/shm.h>


Display* AWindow::_Display = nullptr;
int AWindow::_WinCount = 0;

std::unordered_map<Window, AWindow*> AWindow::WindowLookup;

AWindow::AWindow(unsigned short width, unsigned short height, int posX, int posY, int borderWidth, int* newVisualAttributes, long newXEventMask) : _Width(width), _Height(height) {
    if(!_Display) {
        _Display = XOpenDisplay(nullptr);
    }
    if(!_Display) {
        throw std::runtime_error("Error: XDisplay could not be opened!");
    }

    int supported;
    XkbSetDetectableAutoRepeat(_Display, True, &supported);
    if (!supported) {
        throw std::runtime_error("Error: Detectable autorepeat not supported on this server!\n");
    }

    _VisualInfo = GLContext::GetGLXVisual(newVisualAttributes);

    _ColorMap = XCreateColormap(_Display,
        RootWindow(_Display, _VisualInfo->screen),
        _VisualInfo->visual,
        AllocNone);

    _SWA.colormap = _ColorMap;
    if(newXEventMask != -1) {
        _SWA.event_mask = newXEventMask;
    } else {
        _SWA.event_mask = KeyPressMask | KeyReleaseMask |
                          ButtonPressMask | ButtonReleaseMask |
                          PointerMotionMask | StructureNotifyMask;
    }

    _WindowObj = XCreateWindow(
        _Display,
        RootWindow(_Display, DefaultScreen(_Display)),
        posX, posY, width, height, borderWidth,
        _VisualInfo->depth,
        InputOutput,
        _VisualInfo->visual,
        CWColormap | CWEventMask,
        &_SWA
    );

    if (!_WindowObj) {
        XFree(_VisualInfo);
        throw std::runtime_error("Failed to create X11 window!");
    }

    _XDeleteMessage = XInternAtom(_Display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(_Display, _WindowObj, &_XDeleteMessage, 1);

    _GraphicsContext = XCreateGC(_Display, _WindowObj, 0, NULL);

    //_WMHints = XAllocWMHints();
    //_WMHints->flags = 0;
    _SizeHints = XAllocSizeHints();
    _SizeHints->flags = 0;

    XStoreName(_Display, _WindowObj, "Aksi Window");
    XMapWindow(_Display, _WindowObj);

    WindowLookup[_WindowObj] = this;
    CreateBuffer();

    _WinCount++;
}

AWindow::~AWindow() {
    Close();

    XSync(_Display, False);
    DestroyBuffer();

    //XFree(_WMHints);
    XFree(_SizeHints);
    //_WMHints = nullptr;
    _SizeHints = nullptr;

    if(_Display) {
        if(_GraphicsContext) {
            XFreeGC(_Display, _GraphicsContext);
        }
        if(_WindowObj) {
            XDestroyWindow(_Display, _WindowObj);
        }
        XFreeColormap(_Display, _ColorMap);
        _ColorMap = 0;
        XFree(_VisualInfo);
        _VisualInfo = nullptr;
    }
    _WindowObj = 0;

    XFlush(_Display);
    
    /*if(_WinCount == 0 && _Display) {
        XCloseDisplay(_Display);
        _Display = nullptr;
    }*/
}

void AWindow::Close() {
    if (_Closed || !_Display || !_WindowObj) {
        return;
    }
    _Closed = true;

    if(_Display) {
        if(_WindowObj) {
            XUnmapWindow(_Display, _WindowObj);
        }
    }
    WindowLookup.erase(_WindowObj);
    //_WindowObj = 0;

    XFlush(_Display);

    _WinCount--;
    /*if(_WinCount == 0 && _Display) {
        XCloseDisplay(_Display);
        _Display = nullptr;
    }*/
}


void AWindow::CreateBuffer() {
    if(_Closed) { return; }

    _WinXImage = XShmCreateImage(_Display, _VisualInfo->visual, _VisualInfo->depth,
                             ZPixmap, nullptr, &_SHMInfo, _Width, _Height);
    if (!_WinXImage) {
        std::cerr << "Failed to create XShmImage.\n";
        return;
    }

    _SHMInfo.shmid = shmget(IPC_PRIVATE,
                           _WinXImage->bytes_per_line * _WinXImage->height,
                           IPC_CREAT | 0777);
    _SHMInfo.shmaddr = (char*)shmat(_SHMInfo.shmid, nullptr, 0);
    _WinXImage->data = _SHMInfo.shmaddr;
    _SHMInfo.readOnly = False;

    if (!XShmQueryExtension(_Display)) {
        std::cerr << "MIT-SHM not supported on this display\n";
        return;
    }

    XShmAttach(_Display, &_SHMInfo);
    XSync(_Display, False);
}

void AWindow::DestroyBuffer() {
    if (!_WinXImage) return;

    if(_Display && _SHMInfo.shmaddr) {
        XSync(_Display, False);
        XShmDetach(_Display, &_SHMInfo);
        shmdt(_SHMInfo.shmaddr);
        shmctl(_SHMInfo.shmid, IPC_RMID, nullptr);
    }

    if(_WinXImage) {
        XDestroyImage(_WinXImage);
        _WinXImage = nullptr;
    }

    _SHMInfo.shmaddr = nullptr;
    _SHMInfo.shmid = 0;
}


void AWindow::SetName(const char* name) {
    if(_Closed) { return; }
    XStoreName(_Display, _WindowObj, name);
}

void AWindow::SetPos(const unsigned int x, const unsigned int y) {
    if(_Closed) { return; }
    XMoveWindow(_Display, _WindowObj, x, y);
}

void AWindow::SetPosX(const unsigned int i) {
    if(_Closed) { return; }
    XMoveWindow(_Display, _WindowObj, i, _GWA.y);
}

void AWindow::SetPosY(const unsigned int i) {
    if(_Closed) { return; }
    XMoveWindow(_Display, _WindowObj, _GWA.x, i);
}

void AWindow::SetSize(const unsigned int x, const unsigned int y) {
    if(_Closed) { return; }
    XResizeWindow(_Display, _WindowObj, x, y);
    _Width = x;
    _Height = y;
    ResizeBuffer();
}

void AWindow::SetSizeX(const unsigned int i) {
    if(_Closed) { return; }
    XResizeWindow(_Display, _WindowObj, i, _GWA.height);
    _Width = i;
    ResizeBuffer();
}

void AWindow::SetSizeY(const unsigned int i) {
    if(_Closed) { return; }
    XResizeWindow(_Display, _WindowObj, _GWA.width, i);
    _Height = i;
    ResizeBuffer();
}

void AWindow::SetSizeBounds(const unsigned int minX, const unsigned int minY, const unsigned int maxX, const unsigned int maxY) {
    if(_Closed) { return; }
    _SizeHints->flags |= PMinSize | PMaxSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}

void AWindow::SetSizeMin(const unsigned int minX, const unsigned int minY) {
    if(_Closed) { return; }
    _SizeHints->flags |= PMinSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}

void AWindow::SetSizeMax(const unsigned int maxX, const unsigned int maxY) {
    if(_Closed) { return; }
    _SizeHints->flags |= PMaxSize;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}

void AWindow::ResizeBuffer() {
    if(_Closed) { return; }
    DestroyBuffer();
    CreateBuffer();
}

void AWindow::DisplayWindow() {
    if(_Closed) { return; }
    XShmPutImage(
        _Display,         // Display*
        _WindowObj,       // Drawable (Window)
        _GraphicsContext, // Graphics context
        _WinXImage,       // XImage*
        0, 0,             // src_x, src_y
        0, 0,             // dest_x, dest_y
        _WinXImage->width,
        _WinXImage->height,
        False             // send_event: usually False
    );
    XSync(_Display, False);
}


void AWindow::SetPenCol(int col) {
    penCol = col;
}

void AWindow::Plot(int x, int y) {
    if(_Closed || x >= _Width || x < 0 || y >= _Height || y < 0) { return; }
    XPutPixel(_WinXImage, x, (_Height-1)-y, penCol);
}

void AWindow::Line(int ix1, int iy1, int ix2, int iy2) {
    int x1 = ix1, y1 = iy1;
    int x2 = ix2, y2 = iy2;


    if(std::abs(x2-x1) > std::abs(y2-y1)) {
        if(x1 > x2) {
            x1 = ix2, y1 = iy2;
            x2 = ix1, y2 = iy1;
        }

        int dx = x2-x1;
        int dy = y2-y1;

        int dir = 1;
        if(dy < 0) { dir = -1; }
        dy *= dir;

        int y = y1;
        int D = 2*dy -dx;

        for(int i=0; i<=dx; i++) {
            Plot(x1+i, y);
            if(D >= 0) {
                y += dir;
                D = D - 2*dx;
            }
            D = D + 2*dy;
        }
    } else {
        if(y1 > y2) {
            x1 = ix2, y1 = iy2;
            x2 = ix1, y2 = iy1;
        }

        int dx = x2-x1;
        int dy = y2-y1;

        int dir = 1;
        if(dx < 0) { dir = -1; }
        dx *= dir;

        int x = x1;
        int D = 2*dx -dy;

        for(int i=0; i<=dy; i++) {
            Plot(x, y1+i);
            if(D >= 0) {
                x += dir;
                D = D - 2*dy;
            }
            D = D + 2*dx;
        }
    }
}

void AWindow::Rect(int x, int y, int w, int h) {
    for(int d=0; d<2; d++) {
        for(int ix=0; ix<w; ix++) {
            Plot(x+ix, y+(h*d));
        }
        for(int iy=0; iy<h; iy++) {
            Plot(x+(w*d), y+iy);
        }
    }
}
void AWindow::FillRect(int x, int y, int w, int h) {
    for(int iy=0; iy<h; iy++) {
    for(int ix=0; ix<w; ix++) {
        Plot(x+ix, y+iy);
    }}
}

void AWindow::Arc(int x, int y, int w, int h, int a1, int a2) {
    if(w <= 0 || h <= 0) {
        return;
    }

    float cx = x + w*0.5f;
    float cy = y + h*0.5f;
    float rx = w*0.5f;
    float ry = h*0.5f;

    float start = a1 * M_PI/180.0f;
    float end   = a2 * M_PI/180.0f;

    // step size chosen based on radius
    int rMax = (int)std::max(rx, ry);
    float step = 1.0f / rMax;

    for (float th = start; th <= end; th += step) {
        int px = (int)std::round(cx + rx * std::cos(th));
        int py = (int)std::round(cy + ry * std::sin(th));
        Plot(px -(w*0.5f), py -(h*0.5f));
    }
}
void AWindow::FillArc(int x, int y, int w, int h, int a1, int a2) {
    if(w <= 0 || h <= 0) {
        return;
    }

    float cx = x + w*0.5f;
    float cy = y + h*0.5f;
    float rx = w*0.5f;
    float ry = h*0.5f;

    float start = a1 * M_PI/180.0f;
    float end   = a2 * M_PI/180.0f;

    int rMax = (int)std::max(rx, ry);
    float step = 1.0f / rMax;

    for (float th = start; th <= end; th += step) {
        int px = (int)std::round(cx + rx * std::cos(th));
        int py = (int)std::round(cy + ry * std::sin(th));
        Line(x-(w*0.35f), y-(h*0.35f), px -(w*0.5f), py -(h*0.5f));
        Line(x+(w*0.35f), y+(h*0.35f), px -(w*0.5f), py -(h*0.5f));
    }
}

void AWindow::DrawTexture(Texture2D& tex, int x, int y) {

    int width = tex.GetWidth();
    int height = tex.GetHeight();
    float scaleX = tex.GetScaleX();
    float scaleY = tex.GetScaleY();

    if(width * height * scaleX * scaleY == 0) {
        return;
    }

    int scaledW = static_cast<int>(width * scaleX);
    int scaledH = static_cast<int>(height * scaleY);

    int lastPenCol = penCol;

    for (int iy = 0; iy < scaledH; iy++) {
        int sy = static_cast<int>(iy/scaleY);
        for (int ix = 0; ix < scaledW; ix++) {
            int sx = static_cast<int>(ix/scaleX);

            Vector4 pixel = tex.Sample(sx, sy);
            if(pixel.w >= 128.0f) {
                SetPenCol(((int)pixel.x << 16) | ((int)pixel.y << 8) | (int)pixel.z);
                Plot(ix, iy);
            }
        }
    }

    SetPenCol(lastPenCol);
}

void AWindow::Text(int x, int y, const char* str, int length) const {
    //XDrawString(_Display, _WindowObj, _GraphicsContext, x, y, str, length);
}

void AWindow::GetSize(int& x, int& y) {
    if(_Closed) {
        x = 0;
        y = 0;
    }
    /*XGetWindowAttributes(_Display, _WindowObj, &_GWA);
    _Width = _GWA.width;
    _Height = _GWA.height;*/
    x = _Width;
    y = _Height;
}

void AWindow::HandleWindowEvent(const XEvent& event) {
    if( _Closed) { return; }

    if (event.type == ClientMessage) {
        Close();
    } else if (event.type == ConfigureNotify) {
        unsigned int newWidth = event.xconfigure.width;
        unsigned int newHeight = event.xconfigure.height;

        if(newWidth != _Width || newHeight != _Height) {
            SetSize(event.xconfigure.width, event.xconfigure.height);
        }
    } else if (event.type == Expose) {
        DisplayWindow();
    }
}

void AWindow::FlushDisplay() const {
    XFlush(_Display);
}
