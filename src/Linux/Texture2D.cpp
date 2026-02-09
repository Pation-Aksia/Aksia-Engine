#include "Texture2D.h"

#include "AMath.h"
#include "BitmapHandler.h"

#include <iostream>

Texture2D::Texture2D(const std::string& dir) : directory(dir) {
    if(directory == "") {
        std::cerr << "Error: No directory provided!" << std::endl;
    } else {
        Texture2D::Load();
    }
}

Texture2D::Texture2D() : directory("") {}
Texture2D::~Texture2D() {}

std::ostream& operator<<(std::ostream& os, const Texture2D& i) {
    return os << i.directory;
}


void Texture2D::SetFile(const std::string& dir) {
    directory = dir;
    Texture2D::Load();
}

void Texture2D::Load() {
    pixels.clear();
    pixels.shrink_to_fit();

    if(directory == "") {
        std::cerr << "Error: Texture2D could not be loaded: no directory specified!" << std::endl;
        return;
    }
    BitmapHandler::LoadBMP(directory, width, height, pixels);
}

void Texture2D::SetWidth(int i) { width = i; }
void Texture2D::SetHeight(int i) { height = i; }
void Texture2D::SetSize(int x, int y) { width = x; height = y; }
void Texture2D::SetSize(Vector2 i) {
    width = i.x;
    height = i.y;
}

int Texture2D::GetWidth() { return width; }
int Texture2D::GetHeight() { return height; }
Vector2 Texture2D::GetSize() { return Vector2(width, height); }

void Texture2D::SetCol(Vector4 i, int x, int y) {
    if(x < 0 || x >= width || y < 0 || y >= height) {
        std::cerr << "Error: SetCol x or y out of bounds!" << std::endl;
        return;
    }

    pixels[x + (y*width)] = i;
}
void Texture2D::SetCol(Vector4 i, Vector2 j) {
    if(j.x < 0 || j.x >= width || j.y < 0 || j.y >= height) {
        std::cerr << "Error: SetCol x or y out of bounds!" << std::endl;
        return;
    }

    pixels[j.x + (j.y*width)] = i;
}

Vector4 Texture2D::Sample(int x, int y) {
    return pixels[x + (y*width)];
}

Vector4 Texture2D::Sample(Vector2 i) {
    return pixels[i.x + (i.y*width)];
}