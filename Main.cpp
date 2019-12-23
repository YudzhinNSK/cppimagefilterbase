#include <iostream>
#include "png_toolkit.h"
#include "ReadConf.h"
#include "FiltersFather.h"
#include "AllFilters.h"

int main(int argc, char* argv[])
{
	// toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
	// toolkit near test images!

	try
	{
		if (argc != 4)
			throw "Not enough arguments";

		png_toolkit studTool;
		studTool.load("1.png");
		vector<vector<string>> conf = Config::readConfig(argv[1]);
		conf.reserve(conf.size());
		image_data imd = studTool.getPixelData();
		int i = 0;
		for (const vector<string>& temp : conf) {
			if (temp[i] == "Red") {
				new Red(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
			}
			if (temp[i] == "Threshold") {
				new Threshold(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
			}
			if (temp[i] == "Blur") {
				new Blur(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
			}
			if (temp[i] == "Edge") {
				new Edge(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
			}
			i += 5;
		}
		studTool.save(argv[3]);

	}
	catch (const char* str)
	{
		std::cout << "Error: " << str << std::endl;
		return 1;
	}

	return 0;
}
