#ifndef _AKSI_GL_CONTEXT_CH_
#define _AKSI_GL_CONTEXT_CH_

#include <GL/gl.h>

class AWindow;

class GLContext {
private:

    HGLRC _GLContext;
    static PIXELFORMATDESCRIPTOR _VisualAttributes;
    static AWindow* boundWindow;

public:

    //GLContext(Display* display, XVisualInfo* visualInfo, Window& window, bool makeCurrent = true);
    GLContext(AWindow& window, bool makeCurrent = true);

    ~GLContext();

    GLContext(const GLContext&) = delete;
    GLContext& operator=(const GLContext&) = delete;

    //void FlagWindowBound();
    //void FlagWindowUnbound();

    static int GetGLVisual(HDC hdc);
    static int GetGLVisual(HDC hdc, PIXELFORMATDESCRIPTOR newVisualAttributes);
};

#endif