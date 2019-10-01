#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <array>
#include "stb_image_write.h"
#include "png_toolkit.h"
#include <iostream>

png_toolkit::png_toolkit()
{
}

png_toolkit::~png_toolkit()
{
    stbi_image_free(imgData.pixels);
}

bool png_toolkit::load( const std::string &pictureName )
{
    imgData.pixels = stbi_load(pictureName.c_str(), &imgData.w, &imgData.h, &imgData.compPerPixel, 0);
    return imgData.pixels != nullptr;
}
void png_toolkit::HalfRed()
{
	auto cpp = imgData.compPerPixel;
	if (imgData.compPerPixel == 4 || imgData.compPerPixel == 3)
		for (int i = imgData.h / 2; i < imgData.h; i++)
			for (int j = 0; j < imgData.w * cpp; j += cpp)
			{
				imgData.pixels[i * imgData.w * cpp + j + 0] = 255;
				imgData.pixels[i * imgData.w * cpp + j + 1] = 0;
				imgData.pixels[i * imgData.w * cpp + j + 2] = 0;
			}
}

bool png_toolkit::save( const std::string &pictureName )
{
    return stbi_write_png(pictureName.c_str(),
                   imgData.w, imgData.h,
                   imgData.compPerPixel,
                          imgData.pixels, 0) != 0;
}


image_data png_toolkit::getPixelData( void ) const
{
    return imgData;
}
