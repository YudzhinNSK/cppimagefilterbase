#include <iostream>
#include <vector>
#include <string>
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
		std::cout << "I START WORK";
		return 1;
		if (argc != 4)
			throw "Not enough arguments";
		png_toolkit studTool;
		studTool.load(argv[2]);
		vector<vector<string>> conf = Config::readConfig(argv[1]);
		conf.reserve(conf.size());
		image_data imd = studTool.getPixelData();
		int i = 0;
		for (const vector<string>& temp : conf) {
			if (temp[i] == "Red") {
				new Red(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
				std::cout<<"RED"<< std::endl;
			}
			if (temp[i] == "Threshold") {
				new Threshold(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
				std::cout<<"THRESHOLD"<< std::endl;
			}
			if (temp[i] == "Blur") {
				new Blur(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
				std::cout<<"BLUR"<< std::endl;
			}
			if (temp[i] == "Edge") {
				new Edge(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
				std::cout<<"BLUR"<< std::endl;
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
