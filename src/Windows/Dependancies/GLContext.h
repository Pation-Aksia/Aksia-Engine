#ifndef _AKSI_GL_CONTEXT_CH_
#define _AKSI_GL_CONTEXT_CH_

#include <GL/gl.h>
#include <GL/glx.h>

class AWindow;

class GLContext {
private:

    GLXContext _GLContext;
    static int* _VisualAttributes;
    int _WindowsBoundToGC;

public:

    //GLContext(Display* display, XVisualInfo* visualInfo, Window& window, bool makeCurrent = true);
    GLContext(AWindow& window, bool makeCurrent = true);

    ~GLContext();

    GLContext(const GLContext&) = delete;
    GLContext& operator=(const GLContext&) = delete;

    //void FlagWindowBound();
    //void FlagWindowUnbound();

    static XVisualInfo* GetGLXVisual(int* newVisualAttributes = nullptr);
};

#endif