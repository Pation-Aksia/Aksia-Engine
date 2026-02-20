#include "BitmapHandler.h"

#include "AMath.h"

#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>

bool BitmapHandler::LoadBMP(const std::string& filename, int& width, int& height, std::vector<Vector4>& data) {

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cout << "Error: Unable to open BMP file!" << std::endl;
        file.close();
        return false;
    }

    unsigned char header[54];
    file.read(reinterpret_cast<char*>(header), 54);

    if (header[0] != 'B' || header[1] != 'M') {
        std::cout << "Error: Not a BMP file!" << std::endl;
        file.close();
        return false;
    }

    width   = static_cast<int>(header[18]) | (static_cast<int>(header[19]) << 8) | (static_cast<int>(header[20]) << 16) | (static_cast<int>(header[21]) << 24);
    height  = static_cast<int>(header[22]) | (static_cast<int>(header[23]) << 8) | (static_cast<int>(header[24]) << 16) | (static_cast<int>(header[25]) << 24);
    int bpp = static_cast<int>(header[28]) | (static_cast<int>(header[29]) << 8);

    int dataOffset = *reinterpret_cast<int*>(&header[10]);

    data.resize(width * height);

    file.seekg(dataOffset, std::ios::beg);

    int rowSize;
    int padding;
    if(bpp == 24) {
        rowSize = width * 3;
        padding = (4 - (rowSize % 4)) % 4;
    } else if (bpp == 32) {
        rowSize = width * 4;
        padding = 0;
    } else {
        std::cout << "Error: Unsupported bit depth: " + std::to_string(bpp) << std::endl;
        file.close();
        return false;
    }

    std::vector<uint8_t> row(rowSize);
    for (int y = 0; y < height; y++) {
        file.read(reinterpret_cast<char*>(row.data()), rowSize);
        for (int x = 0; x < width; x++) {
            int idx = x * (bpp / 8);
            if (bpp == 24) {
                data[y * width + x] = Vector4(
                    row[idx + 2], // R
                    row[idx + 1], // G
                    row[idx + 0], // B
                    255.0f        // A
                );
            } else if (bpp == 32) {
                data[y * width + x] = Vector4(
                    row[idx + 2], // R
                    row[idx + 1], // G
                    row[idx + 0], // B
                    row[idx + 3]  // A
                );
            }
        }
        file.seekg(padding, std::ios::cur);
    }

    file.close();

    return true;
}