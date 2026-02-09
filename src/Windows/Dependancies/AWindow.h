#ifndef _AKSI_WINDOW_CH_
#define _AKSI_WINDOW_CH_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

class Texture2D;


class AWindow {
private:

    static Display* _Display;
    static int _WinCount;

    Window _WindowObj;
    GC _GraphicsContext;
    Colormap _ColorMap;
    XSetWindowAttributes _SWA;
    XWindowAttributes _GWA;
    XVisualInfo* _VisualInfo;
    //XWMHints* _WMHints;
    XSizeHints* _SizeHints;

public:

    //-Constructor-----Destructor-
    AWindow(int width = 640, int height = 480, int posX = 0, int posY = 0, int borderWidth = 0, int* newVisualAttributes = nullptr, long newXEventMask = -1);

    ~AWindow();

    //-Disable-Copy/Move-
    AWindow(const AWindow&) = delete;
    AWindow& operator=(const AWindow&) = delete;

    //-Regular-Functions-

    static Display* GetSharedDisplay() { return _Display; }

    void SetName(const char* name);

    void SetPos(const unsigned int x, const unsigned int y);
    void SetPosX(const unsigned int i);
    void SetPosY(const unsigned int i);
    void SetSize(const unsigned int x, const unsigned int y);
    void SetSizeX(const unsigned int i);
    void SetSizeY(const unsigned int i);
    void SetSizeBounds(const unsigned int minX, const unsigned int minY, const unsigned int maxX, const unsigned int maxY);
    void SetSizeMin(const unsigned int minX, const unsigned int minY);
    void SetSizeMax(const unsigned int maxX, const unsigned int maxY);

    XVisualInfo* GetVisualInfo() { return _VisualInfo; }
    Window& GetWindowObject() { return _WindowObj; }

    //-Drawing-Primitives-

    void SetPenCol(int col);

    void Plot(int x, int y);
    void Plot(XPoint* points, int count, int mode = 0);

    void Line(int x1, int y1, int x2, int y2);
    void Lines(XPoint* points, int count, int mode = 0);

    void Rect(int x, int y, int w, int h);
    void FillRect(int x, int y, int w, int h);

    void Arc(int x, int y, int w, int h, int a1, int a2);
    void FillArc(int x, int y, int w, int h, int a1, int a2);

    void Poly(XPoint* points, int count, int shape, int mode = CoordModeOrigin);

    void DrawTexture(Texture2D& tex, int x, int y, float scaleX = 1, float scaleY = 1);
    
    void Text(int x, int y, const char* str, int length) const;


    void GetSize(int& x, int& y);

    void FlushDisplay() const;
};

#endif //_AKSI_WINDOW_CH_