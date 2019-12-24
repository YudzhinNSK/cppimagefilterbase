#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Config {
public:
	static vector<vector<string>> readConfig(string path);
};