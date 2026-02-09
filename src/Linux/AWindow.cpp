#include "AWindow.h"

#include "AMath.h"
#include "GLContext.h"
#include "Texture2D.h"

#include <iostream>
#include <string>


Display* AWindow::_Display = nullptr;
int AWindow::_WinCount = 0;

AWindow::AWindow(int width, int height, int posX, int posY, int borderWidth, int* newVisualAttributes, long newXEventMask) {
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

    _GraphicsContext = XCreateGC(_Display, _WindowObj, 0, NULL);

    //_WMHints = XAllocWMHints();
    //_WMHints->flags = 0;
    _SizeHints = XAllocSizeHints();
    _SizeHints->flags = 0;

    XStoreName(_Display, _WindowObj, "Aksi Window");
    XMapWindow(_Display, _WindowObj);
    XFlush(_Display);

    _WinCount++;
}

AWindow::~AWindow() {
    //XFree(_WMHints);
    XFree(_SizeHints);

    if(_Display) {
        if(_GraphicsContext) {
            XFreeGC(_Display, _GraphicsContext);
        }
        if(_WindowObj) {
            XUnmapWindow(_Display, _WindowObj);
            XDestroyWindow(_Display, _WindowObj);
        }
        XFreeColormap(_Display, _ColorMap);
        XFlush(_Display);
        XFree(_VisualInfo);
    }

    _WinCount--;
    if(_WinCount == 0 && _Display) {
        XCloseDisplay(_Display);
        _Display = nullptr;
    }
}


void AWindow::SetName(const char* name) {
    XStoreName(_Display, _WindowObj, name);
}

void AWindow::SetPos(const unsigned int x, const unsigned int y) {
    XMoveWindow(_Display, _WindowObj, x, y);
}

void AWindow::SetPosX(const unsigned int i) {
    XMoveWindow(_Display, _WindowObj, i, _GWA.y);
}

void AWindow::SetPosY(const unsigned int i) {
    XMoveWindow(_Display, _WindowObj, _GWA.x, i);
}

void AWindow::SetSize(const unsigned int x, const unsigned int y) {
    XResizeWindow(_Display, _WindowObj, x, y);
}

void AWindow::SetSizeX(const unsigned int i) {
    XResizeWindow(_Display, _WindowObj, i, _GWA.height);
}

void AWindow::SetSizeY(const unsigned int i) {
    XResizeWindow(_Display, _WindowObj, _GWA.width, i);
}

void AWindow::SetSizeBounds(const unsigned int minX, const unsigned int minY, const unsigned int maxX, const unsigned int maxY) {
    _SizeHints->flags |= PMinSize | PMaxSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}

void AWindow::SetSizeMin(const unsigned int minX, const unsigned int minY) {
    _SizeHints->flags |= PMinSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}

void AWindow::SetSizeMax(const unsigned int maxX, const unsigned int maxY) {
    _SizeHints->flags |= PMaxSize;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);
}


void AWindow::SetPenCol(int col) {
    XSetForeground(_Display, _GraphicsContext, col);
}

void AWindow::Plot(int x, int y) {
    XDrawPoint(_Display, _WindowObj, _GraphicsContext, x, y);
}
void AWindow::Plot(XPoint* points, int count, int mode) {
    XDrawPoints(_Display, _WindowObj, _GraphicsContext, points, count, mode);
}

void AWindow::Line(int x1, int y1, int x2, int y2) {
    XDrawLine(_Display, _WindowObj, _GraphicsContext, x1, y1, x2, y2);
}
void AWindow::Lines(XPoint* points, int count, int mode) {
    XDrawLines(_Display, _WindowObj, _GraphicsContext, points, count, mode);
}

void AWindow::Rect(int x, int y, int w, int h) {
    XDrawRectangle(_Display, _WindowObj, _GraphicsContext, x, y, w, h);
}
void AWindow::FillRect(int x, int y, int w, int h) {
    XFillRectangle(_Display, _WindowObj, _GraphicsContext, x, y, w, h);
}

void AWindow::Arc(int x, int y, int w, int h, int a1, int a2) {
    XDrawArc(_Display, _WindowObj, _GraphicsContext, x-(w*0.5f), y-(h*0.5f), w, h, a1*64, a2*64);
}
void AWindow::FillArc(int x, int y, int w, int h, int a1, int a2) {
    XFillArc(_Display, _WindowObj, _GraphicsContext, x-(w*0.5f), y-(h*0.5f), w, h, a1*64, a2*64);
}

void AWindow::Poly(XPoint* points, int count, int shape, int mode) {
    XFillPolygon(_Display, _WindowObj, _GraphicsContext, points, count, shape, mode);
}

void AWindow::DrawTexture(Texture2D& tex, int x, int y, float scaleX, float scaleY) {
    if(tex.GetWidth() * tex.GetHeight() == 0) {
        return;
    }
    XGetWindowAttributes(_Display, _WindowObj, &_GWA);
    for(int iy=0; iy<(int)(tex.GetHeight()*scaleY); iy++) {
    for(int ix=0; ix<(int)(tex.GetWidth()*scaleX); ix++) {
        Vector4 col = tex.Sample(ix/scaleX, iy/scaleY);
        XSetForeground(_Display, _GraphicsContext, ((int)col.x << 16)|((int)col.y << 8)|(int)col.z);
        XDrawPoint(_Display, _WindowObj, _GraphicsContext, x+ix, _GWA.height-(y+iy+1));
    }}
}

void AWindow::Text(int x, int y, const char* str, int length) const {
    XDrawString(_Display, _WindowObj, _GraphicsContext, x, y, str, length);
}

void AWindow::GetSize(int& x, int& y) {
    XGetWindowAttributes(_Display, _WindowObj, &_GWA);
    x = _GWA.width;
    y = _GWA.height;
}

void AWindow::FlushDisplay() const {
    XFlush(_Display);
}
