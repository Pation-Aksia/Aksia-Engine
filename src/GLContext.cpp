#include "GLContext.h"
#include "AWindow.h"

static int defVIAT[] = {
    GLX_RGBA,
    GLX_DEPTH_SIZE, 24,
    GLX_DOUBLEBUFFER,
    None
};

int* GLContext::_VisualAttributes = defVIAT;

GLContext::GLContext(AWindow& window, bool makeCurrent) {
    Display* TMP_Display_ptr = AWindow::GetSharedDisplay();
    XVisualInfo* TMP_VI_ptr = window.GetVisualInfo();

    _GLContext = glXCreateContext(TMP_Display_ptr, TMP_VI_ptr, nullptr, GL_TRUE);
    if(makeCurrent) {
        glXMakeCurrent(TMP_Display_ptr, window.GetWindowObject(), _GLContext);
    }
}

GLContext::~GLContext() {
    glXDestroyContext(AWindow::GetSharedDisplay(), _GLContext);
    //delete(GLContext::_VisualAttributes);
    GLContext::_VisualAttributes = nullptr;
}

XVisualInfo* GLContext::GetGLXVisual(int* newVisualAttributes) {
    if(newVisualAttributes) {
        GLContext::_VisualAttributes = newVisualAttributes;
    }
    Display* TMP_Display_ptr = AWindow::GetSharedDisplay();
    return glXChooseVisual(TMP_Display_ptr, DefaultScreen(TMP_Display_ptr), _VisualAttributes);
}


//void GLContext::FlagWindowBound() { GLContext::_WindowsBoundToGC++; }
//void GLContext::FlagWindowUnbound() { GLContext::_WindowsBoundToGC--; }