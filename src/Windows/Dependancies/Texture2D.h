#ifndef _AKSI_TEX_2D_CH_
#define _AKSI_TEX_2D_CH_

#include <string>
#include <vector>

#include <iosfwd>

class Vector2;
class Vector4;

class Texture2D {
private:
    int width, height;

    std::vector<Vector4> pixels;

    std::string directory;

public:
    Texture2D(const std::string& dir = "");
    Texture2D();
    ~Texture2D();

    friend std::ostream& operator<<(std::ostream& os, const Texture2D& i);


    void SetFile(const std::string& dir = "");

    void Load();

    void SetWidth(int i);
    void SetHeight(int i);
    void SetSize(int x, int y);
    void SetSize(Vector2 i);

    int GetWidth();
    int GetHeight();
    Vector2 GetSize();

    void SetCol(Vector4 i, int x=0, int y=0);
    void SetCol(Vector4 i, Vector2 j);

    Vector4 Sample(int x=0, int y=0);
    Vector4 Sample(Vector2 i);
};

#endif