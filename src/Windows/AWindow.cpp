#include "AWindow.h"

#include "AMath.h"
#include "GLContext.h"
#include "Texture2D.h"

#include <iostream>
#include <string>


LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

int AWindow::_WinCount = 0;

AWindow::AWindow(HINSTANCE hInstance, int width, int height, int posX, int posY, LPCSTR name /*, PIXELFORMATDESCRIPTOR newVisualAttributes = {0}*/ /*set this in GLContextCreation probably*/) {

    WNDCLASSA wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = "AWindowClass";
    wc.style         = CS_OWNDC;

    RegisterClassA(&wc);

    _WindowObj = CreateWindowA(
        "AWindowClass",
        name,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        posX,
        posY,
        width,
        height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!_WindowObj) {
        throw std::runtime_error("Failed to create window!");
    }

    _hdc = GetDC(_WindowObj);

    /*if(newVisualAttributes.nSize = 0) {
        _VisualInfo = GLContext::GetGLVisual(newVisualAttributes);
    }*/

    _VisualInfo = GLContext::GetGLVisual(_hdc);

    //_GraphicsContext = XCreateGC(_Display, _WindowObj, 0, NULL);

    _WinCount++;
}

AWindow::~AWindow() {}

void AWindow::SetName(const char* name) {
    SetWindowTextA(_WindowObj, name);
}

void AWindow::SetPos(const unsigned int x, const unsigned int y) {
    //XMoveWindow(_Display, _WindowObj, x, y);
}

void AWindow::SetPosX(const unsigned int i) {
    //XMoveWindow(_Display, _WindowObj, i, _GWA.y);
}

void AWindow::SetPosY(const unsigned int i) {
    //XMoveWindow(_Display, _WindowObj, _GWA.x, i);
}

void AWindow::SetSize(const unsigned int x, const unsigned int y) {
    ///XResizeWindow(_Display, _WindowObj, x, y);
}

void AWindow::SetSizeX(const unsigned int i) {
    //XResizeWindow(_Display, _WindowObj, i, _GWA.height);
}

void AWindow::SetSizeY(const unsigned int i) {
    //XResizeWindow(_Display, _WindowObj, _GWA.width, i);
}

void AWindow::SetSizeBounds(const unsigned int minX, const unsigned int minY, const unsigned int maxX, const unsigned int maxY) {
    /*_SizeHints->flags |= PMinSize | PMaxSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);*/
}

void AWindow::SetSizeMin(const unsigned int minX, const unsigned int minY) {
    /*_SizeHints->flags |= PMinSize;
    _SizeHints->min_width = minX;
    _SizeHints->min_height = minY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);*/
}

void AWindow::SetSizeMax(const unsigned int maxX, const unsigned int maxY) {
    /*_SizeHints->flags |= PMaxSize;
    _SizeHints->max_width = maxX;
    _SizeHints->max_height = maxY;
    XSetNormalHints(_Display, _WindowObj, _SizeHints);*/
}


void AWindow::SetPenCol(int col) {
    //XSetForeground(_Display, _GraphicsContext, col);
}

void AWindow::Plot(int x, int y) {
    //XDrawPoint(_Display, _WindowObj, _GraphicsContext, x, y);
}
void AWindow::Plot(int* points, int count, int mode) {
    //XDrawPoints(_Display, _WindowObj, _GraphicsContext, points, count, mode);
}

void AWindow::Line(int x1, int y1, int x2, int y2) {
    //XDrawLine(_Display, _WindowObj, _GraphicsContext, x1, y1, x2, y2);
}
void AWindow::Lines(int* points, int count, int mode) {
    //XDrawLines(_Display, _WindowObj, _GraphicsContext, points, count, mode);
}

void AWindow::Rect(int x, int y, int w, int h) {
    //XDrawRectangle(_Display, _WindowObj, _GraphicsContext, x, y, w, h);
}
void AWindow::FillRect(int x, int y, int w, int h) {
    //XFillRectangle(_Display, _WindowObj, _GraphicsContext, x, y, w, h);
}

void AWindow::Arc(int x, int y, int w, int h, int a1, int a2) {
    //XDrawArc(_Display, _WindowObj, _GraphicsContext, x-(w*0.5f), y-(h*0.5f), w, h, a1*64, a2*64);
}
void AWindow::FillArc(int x, int y, int w, int h, int a1, int a2) {
    //XFillArc(_Display, _WindowObj, _GraphicsContext, x-(w*0.5f), y-(h*0.5f), w, h, a1*64, a2*64);
}

void AWindow::Poly(int* points, int count, int shape, int mode) {
    //XFillPolygon(_Display, _WindowObj, _GraphicsContext, points, count, shape, mode);
}

void AWindow::DrawTexture(Texture2D& tex, int x, int y, float scaleX, float scaleY) {
    /*if(tex.GetWidth() * tex.GetHeight() == 0) {
        return;
    }
    XGetWindowAttributes(_Display, _WindowObj, &_GWA);
    for(int iy=0; iy<(int)(tex.GetHeight()*scaleY); iy++) {
    for(int ix=0; ix<(int)(tex.GetWidth()*scaleX); ix++) {
        Vector4 col = tex.Sample(ix/scaleX, iy/scaleY);
        XSetForeground(_Display, _GraphicsContext, ((int)col.x << 16)|((int)col.y << 8)|(int)col.z);
        XDrawPoint(_Display, _WindowObj, _GraphicsContext, x+ix, _GWA.height-(y+iy+1));
    }}*/
}

void AWindow::Text(int x, int y, const char* str, int length) const {
    //XDrawString(_Display, _WindowObj, _GraphicsContext, x, y, str, length);
}

void AWindow::GetSize(int& x, int& y) {
    /*XGetWindowAttributes(_Display, _WindowObj, &_GWA);
    x = _GWA.width;
    y = _GWA.height;*/
}

void AWindow::FlushDisplay() const {
    //XFlush(_Display);
}
