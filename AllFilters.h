#pragma once
#include "FiltersFather.h"
#include <algorithm>

void FiltersFather::BW(image_data&, int u, int l, int b, int r) {
	int curpix;
	int green, red, blue;
	int bw;
	for (int k = up; k < bt; k++) {
		for (int i = lf; i < rh; i++) {
			curpix = imd.compPerPixel * (k * imd.w + i);
			red = imd.pixels[curpix];
			green = imd.pixels[curpix + 1];
			blue = imd.pixels[curpix + 2];
			bw = (3 * red + 6 * green + blue) / 10;
			imd.pixels[curpix] = bw;
			imd.pixels[curpix + 1] = bw;
			imd.pixels[curpix + 2] = bw;
		}
	}
}

class Red : public FiltersFather {
public:
	Red(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {
		int curpix;
		for (int k = up; k < bt; k++) {
			for (int i = lf; i < rh; i++) {
				curpix = imd.compPerPixel * (k * imd.w + i);
				imd.pixels[curpix] = 255;
				imd.pixels[curpix + 1] = 0;
				imd.pixels[curpix + 2] = 0;
			}
		}
	}
};

class Threshold : public FiltersFather {
public:
	Threshold(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {
		BW(imd, up, lf, bt, rh);
		image_data copy;
		copy.h = imd.h;
		copy.w = imd.w;
		copy.compPerPixel = imd.compPerPixel;
		int img_size = imd.w * imd.h * imd.compPerPixel;
		copy.pixels = new stbi_uc[img_size];
		memcpy(copy.pixels, imd.pixels, img_size);
		int median;
		int curpix;
		for (int j = up; j < bt; j++) {
			for (int i = lf; i < rh; i++) {
				curpix = imd.compPerPixel * (j * imd.w + i);
				int upp = j - 2;
				int bottom = j + 2;
				int left = i - 2;
				int right = i + 2;
				vector<stbi_uc> elem;
				for (int m = upp; m <= bottom; m++) {
					for (int l = left; l <= right; l++) {
						int cp;
						if ((l < lf) || (l > rh) || (m < up) || (m > bt)) {
							continue;
						}
						cp = copy.compPerPixel * (m * copy.w + l);
						elem.push_back(copy.pixels[cp]);
					}
				}
				std::sort(elem.begin(), elem.end());
				median = elem[elem.size() / 2];
				if (imd.pixels[curpix] < median) {
					imd.pixels[curpix] = 0;
					imd.pixels[curpix + 1] = 0;
					imd.pixels[curpix + 2] = 0;
				}
			}
		}
		delete[] copy.pixels;
	}
};

class Blur : public FiltersFather {
public:
	Blur(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {
		image_data copy;
		copy.h = imd.h;
		copy.w = imd.w;
		copy.compPerPixel = imd.compPerPixel;
		int img_size = imd.w * imd.h * imd.compPerPixel;
		copy.pixels = new stbi_uc[img_size];
		memcpy(copy.pixels, imd.pixels, img_size);
		int curpix;
		for (int j = up; j < bt; j++) {
			for (int i = lf; i < rh; i++) {
				curpix = imd.compPerPixel * (j * imd.w + i);
				int upp = j - 1;
				int bottom = j + 1;
				int left = i - 1;
				int right = i + 1;
				int val[3] = { 0,0,0 };
				for (int m = upp; m <= bottom; m++) {
					for (int l = left; l <= right; l++) {
						int cp;
						if ((m < up) || (m > bt) || (l < lf) || (l > rh)) {
							continue;
						}
						cp = copy.compPerPixel * (m * copy.w + l);
						val[0] += copy.pixels[cp];
						val[1] += copy.pixels[cp + 1];
						val[2] += copy.pixels[cp + 2];
					}
				}
				imd.pixels[curpix] = val[0] / 9;
				imd.pixels[curpix + 1] = val[1] / 9;
				imd.pixels[curpix + 2] = val[2] / 9;
			}
		}
		delete[] copy.pixels;
	}
};

class Edge : public FiltersFather {
public:
	Edge(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {
		BW(imd, up, lf, bt, rh);
		image_data copy;
		copy.h = imd.h;
		copy.w = imd.w;
		copy.compPerPixel = imd.compPerPixel;
		int img_size = imd.w * imd.h * imd.compPerPixel;
		copy.pixels = new stbi_uc[img_size];
		memcpy(copy.pixels, imd.pixels, img_size);
		int curpix;
		for (int j = up; j < bt; j++) {
			for (int i = lf; i < rh; i++) {
				curpix = imd.compPerPixel * (j * imd.w + i);
				int upp = j - 1;
				int bottom = j + 1;
				int left = i - 1;
				int right = i + 1;
				int sum = 0;
				int placeneeded = 5;
				int place = 0;
				for (int m = upp; m <= bottom; m++) {
					for (int l = left; l <= right; l++) {
						int cp;
						place++;
						if ((m < up) || (m > bt) || (l < lf) || (l > rh)) {
							continue;
						}
						cp = copy.compPerPixel * (m * copy.w + l);
						if (place == placeneeded) {
							sum += 9 * copy.pixels[cp];
						}
						else {
							sum -= copy.pixels[cp];
						}
					}
				}
				if (sum > 255) {
					sum = 255;
				}
				else {
					if (sum < 0) {
						sum = 0;
					}
				}
				imd.pixels[curpix] = sum;
				imd.pixels[curpix + 1] = sum;
				imd.pixels[curpix + 2] = sum;
			}
		}
		delete[] copy.pixels;
	}
};
