#pragma once
#include "FiltersFather.h"
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


class Red : public FiltersFather {
public:
	Red(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {}
	void applyfilter();
};

class Threshold : public FiltersFather {
public:
	Threshold(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {}
	void applyfilter();
};

class Blur : public FiltersFather {
public:
	Blur(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {}
	void applyfilter();
};

class Edge : public FiltersFather {
public:
	Edge(image_data& imd, int u, int l, int b, int r) : FiltersFather(imd, u, l, b, r) {}
	void applyfilter();
};
