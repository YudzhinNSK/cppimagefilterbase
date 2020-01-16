#pragma once
#include "png_toolkit.h"
#include "stb_image.h"
#include "stb_image_write.h"

class FiltersFather {
protected:
	image_data& imd;
	int up = 0, lf = 0, bt = 0, rh = 0;
public:
	FiltersFather(image_data& imd, int u, int l, int b, int r) : imd(imd) {
		if (u != 0) {
			up = imd.h / u;
		}
		if (l != 0) {
			lf = imd.w / l;
		}
		if (b != 0) {
			bt = imd.h / b;
		}
		if (r != 0) {
			rh = imd.w / r;
		}
	}

	void BW(image_data& imd, int u, int l, int b, int r);

	image_data copy_picture(image_data& imd, int u, int l, int b, int r);

	int CheckSum(int x) {
		if (x > 255) {
			x = 255;
		}
		if (x < 0) {
			x = 0;
		}
		return x;
	}
	
	bool CheckBounds(int x, int y) {
		if ((x < up) || (x >= bt) || (y < lf) || (y >= rh))
			return false;
		else
			return true;
	}
};