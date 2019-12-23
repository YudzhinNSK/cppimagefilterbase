#include "ReadConf.h"
#include <fstream>
#include <sstream>
vector<vector<string>> Config::readConfig(string path) {
	string Delimeter = " ";
	string str;
	string num;
	int i = 0;
	vector<vector<string>> outData;
	vector<string> FiltersData;
	ifstream inputData(path);
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