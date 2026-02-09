#ifndef _AKSI_WINDOW_CH_
#define _AKSI_WINDOW_CH_

#include <windows.h>

class Texture2D;


class AWindow {
private:

    HDC _hdc;
    static int _WinCount;

    HWND _WindowObj;
    ///GC _GraphicsContext;
    int _VisualInfo;

public:

    //-Constructor-----Destructor-
    AWindow(HINSTANCE hInstance, int width = 640, int height = 480, int posX = 0, int posY = 0, LPCSTR name = "window");

    ~AWindow();

    //-Disable-Copy/Move-
    AWindow(const AWindow&) = delete;
    AWindow& operator=(const AWindow&) = delete;

    //-Regular-Functions-

    HDC& GetHDC() { return _hdc; }

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

    int GetVisualInfo() { return _VisualInfo; }
    HWND& GetWindowObject() { return _WindowObj; }

    //-Drawing-Primitives-

    void SetPenCol(int col);

    void Plot(int x, int y);
    void Plot(int* points, int count, int mode = 0);

    void Line(int x1, int y1, int x2, int y2);
    void Lines(int* points, int count, int mode = 0);

    void Rect(int x, int y, int w, int h);
    void FillRect(int x, int y, int w, int h);

    void Arc(int x, int y, int w, int h, int a1, int a2);
    void FillArc(int x, int y, int w, int h, int a1, int a2);

    void Poly(int* points, int count, int shape, int mode = 0);

    void DrawTexture(Texture2D& tex, int x, int y, float scaleX = 1, float scaleY = 1);
    
    void Text(int x, int y, const char* str, int length) const;


    void GetSize(int& x, int& y);

    void FlushDisplay() const;
};

#endif //_AKSI_WINDOW_CH_