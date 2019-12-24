#pragma once

#include <string>
#include <map>
#include "stb_image.h"

using namespace std;

struct image_data
{
    stbi_uc* pixels;
    int w, h;
    int compPerPixel;
};

class png_toolkit
{
public:
    enum class Error {
        WrongSize,
        WrongFormat,
        Ok
    };

    png_toolkit();
    ~png_toolkit();
    void HalfRed(void);
    bool load(std::string const& pictureName);
    bool save(std::string const& pictureName);
    image_data getPixelData(void) const;

private:
    image_data imgData;

};