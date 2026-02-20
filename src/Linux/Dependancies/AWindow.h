#ifndef _AKSI_WINDOW_CH_
#define _AKSI_WINDOW_CH_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#include <X11/extensions/XShm.h>

#include <unordered_map>

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

    Atom _XDeleteMessage;
    bool _Closed = false;

    XShmSegmentInfo _SHMInfo;
    XImage* _WinXImage = nullptr;

    XVisualInfo* _VisualInfo;
    //XWMHints* _WMHints;
    XSizeHints* _SizeHints;

    unsigned short _Width;
    unsigned short _Height;

    int penCol;
    bool invertPlotY = false;

    void CreateBuffer();
    void DestroyBuffer();

public:

    static std::unordered_map<Window, AWindow*> WindowLookup;

    //-Constructor-----Destructor-
    AWindow(unsigned short width = 640, unsigned short height = 480, int posX = 0, int posY = 0, int borderWidth = 0, int* newVisualAttributes = nullptr, long newXEventMask = -1);

    ~AWindow();

    //-Disable-Copy/Move-
    AWindow(const AWindow&) = delete;
    AWindow& operator=(const AWindow&) = delete;

    //-Regular-Functions-

    static Display* GetSharedDisplay() { return _Display; }

    void Close();
    bool IsClosed() const { return _Closed; }

    static int GetWinCount(){ return _WinCount; }

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

    void ResizeBuffer();

    void DisplayWindow();


    void SetPenCol(int col);

    void Plot(int x, int y);

    void Line(int x1, int y1, int x2, int y2);

    void Rect(int x, int y, int w, int h);
    void FillRect(int x, int y, int w, int h);

    void Arc(int x, int y, int w, int h, int a1, int a2);
    void FillArc(int x, int y, int w, int h, int a1, int a2);

    void DrawTexture(Texture2D& tex, int x, int y);
    
    void Text(int x, int y, const char* str, int length) const;


    void GetSize(int& x, int& y);

    void HandleWindowEvent(const XEvent& event);

    void FlushDisplay() const;
};

#endif //_AKSI_WINDOW_CH_