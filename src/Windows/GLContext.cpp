#include "GLContext.h"
#include "AWindow.h"

#include <wingdi.h>

#include <iostream>

PIXELFORMATDESCRIPTOR defPFD = {
    sizeof(PIXELFORMATDESCRIPTOR),  // nSize
    1,                              // nVersion
    PFD_DRAW_TO_WINDOW |            // dwFlags
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER |
    PFD_GENERIC_ACCELERATED,
    PFD_TYPE_RGBA,                  // iPixelType
    32,                             // cColorBits
    0,                              // cRedBits
    0,                              // cRedShift
    0,                              // cGreenBits
    0,                              // cGreenShift
    0,                              // cBlueBits
    0,                              // cBlueShift
    8,                              // cAlphaBits
    0,                              // cAlphaShift
    0,                              // cAccumBits
    0,                              // cAccumRedBits
    0,                              // cAccumGreenBits
    0,                              // cAccumBlueBits
    0,                              // cAccumAlphaBits
    24,                             // cDepthBits
    8,                              // cStencilBits
    0,                              // cAuxBuffers
    PFD_MAIN_PLANE,                 // iLayerType
    0,                              // bReserved
    0,                              // dwLayerMask
    0,                              // dwVisibleMask
    0                               // dwDamageMask
};

PIXELFORMATDESCRIPTOR GLContext::_VisualAttributes = defPFD;
AWindow* GLContext::boundWindow = nullptr;

GLContext::GLContext(AWindow& window, bool makeCurrent) {
    boundWindow = &window;
    HDC TMP_Device = boundWindow->GetHDC();

    SetPixelFormat(TMP_Device, boundWindow->GetVisualInfo(), &_VisualAttributes);

    _GLContext = wglCreateContext(TMP_Device);
    if(makeCurrent) {
        wglMakeCurrent(TMP_Device, _GLContext);
    }
}

GLContext::~GLContext() {
    wglDeleteContext(_GLContext);
    boundWindow = nullptr;
    //GLContext::_VisualAttributes = nullptr;
}

int GLContext::GetGLVisual(HDC hdc) {
    return ChoosePixelFormat(hdc, &_VisualAttributes);
}

int GLContext::GetGLVisual(HDC hdc, PIXELFORMATDESCRIPTOR newVisualAttributes) {
    GLContext::_VisualAttributes = newVisualAttributes;
    return ChoosePixelFormat(hdc, &_VisualAttributes);
}


//void GLContext::FlagWindowBound() { GLContext::_WindowsBoundToGC++; }
//void GLContext::FlagWindowUnbound() { GLContext::_WindowsBoundToGC--; }