#ifndef _AKSI_BMP_HANDLER_CH_
#define _AKSI_BMP_HANDLER_CH_

#include <string>
#include <vector>

class Vector4;

class BitmapHandler {
public:
    static bool LoadBMP(const std::string& filename, int& width, int& height, std::vector<Vector4>& data);
};

#endif