#pragma once
#include "png_toolkit.h"
#include "stb_image.h"
#include "stb_image_write.h"

class FiltersFather {
public:
	image_data& imd;
	int up = 0, lf = 0, bt = 0, rh = 0;
	FiltersFather(image_data& imd, int u, int l, int b, int r) : imd(imd){
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

	bool ChechSpace(int x, int y) {
		if ((x < lf) || (x > rh) || (y < bt) || (y > up)) {
			return false;
		}
		return true;
	}
};