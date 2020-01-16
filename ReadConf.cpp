#include "Config.h"
#include <fstream>
#include<sstream>
#include <string>
#include <iostream>
using namespace std;
vector<vector<string>> Config::readConfig(string path) {
	string str;
	string num;
	int i = 0;
	vector<vector<string>> outData;
	vector<string> FiltersData;
	std::ifstream inputData(path);
	if (inputData.is_open()) {
		while (getline(inputData, str)) {
			stringstream ss(str);
			while (ss) {
				string s;
				ss >> s;
				i++;
				if (i < 6) {
					FiltersData.push_back(s);
				}
			}
			i = 0;
			outData.push_back(FiltersData);
		}
		inputData.close();
	}
	return outData;
}
