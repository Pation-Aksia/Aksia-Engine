#ifndef _AKSI_TEX_2D_CH_
#define _AKSI_TEX_2D_CH_

#include <X11/Xlib.h>

#include <string>
#include <vector>
#include <cstdint>

#include <iosfwd>

class Vector2;
class Vector4;

class Texture2D {
private:

    int width = 0, height = 0;
    float scaleX = 1, scaleY = 1;

    std::vector<Vector4> pixels;

    std::string directory;

public:
    Texture2D(const std::string& dir = "");
    Texture2D();
    ~Texture2D();

    friend std::ostream& operator<<(std::ostream& os, const Texture2D& i);


    void SetFile(const std::string& dir = "");

    void Load();
    void LoadPixelChanges();

    void SetWidth(int i);
    void SetHeight(int i);
    void SetSize(int x, int y);
    void SetSize(Vector2 i);
    void SetScale(float x, float y);
    void SetScale(Vector2 i);

    int GetWidth();
    int GetHeight();
    Vector2 GetSize();

    float GetScaleX();
    float GetScaleY();
    Vector2 GetScale();

    void SetCol(Vector4 i, int x=0, int y=0);
    void SetCol(Vector4 i, Vector2 j);

    Vector4 Sample(int x=0, int y=0);
    Vector4 Sample(Vector2 i);
    Vector4 SampleUV(float x=0.0f, float y=0.0f);
    Vector4 SampleUV(Vector2 i);
};

#endif