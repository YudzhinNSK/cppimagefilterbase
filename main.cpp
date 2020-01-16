#include <iostream>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include "png_toolkit.h"
#include "Config.h"
#include "FiltersFather.h"
#include "AllFilters.h"

using namespace std;

int main(int argc, char* argv[])
{
    // toolkit filter_name base_pic_name sudent_tool student_pic_name limitPix limitMSE
    // toolkit near test images!

    try{
        if (argc != 4)
            throw "Not enough arguments";

        png_toolkit studTool;
        studTool.load(argv[2]);//"1.jpg");//
        vector<vector<string>> conf = Config::readConfig(argv[1]);//"config.txt");// 
        conf.reserve(conf.size());
        image_data imd = studTool.getPixelData();
        int i = 0;
        for (const vector<string>& temp : conf){
            if (temp[i] == "Red") {
                Red* red = new Red(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
                red->applyfilter();
            }
            if (temp[i] == "Threshold") {
                Threshold* thr = new Threshold(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
                thr->applyfilter();
            }
            if (temp[i] == "Blur") {
                Blur* blur = new Blur(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
                blur->applyfilter();
            }
            if (temp[i] == "Edge") {
                Edge* edge = new Edge(imd, stoi(temp[i + 1]), stoi(temp[i + 2]), stoi(temp[i + 3]), stoi(temp[i + 4]));
                edge->applyfilter();
            }
            i += 5;
        }
        studTool.save(argv[3]);//"2.png");// 
    }

    catch (const char* str){
        std::cout << "Error: " << str << std::endl;
        return 1;
    }

    return 0;
}
