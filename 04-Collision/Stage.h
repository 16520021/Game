#pragma once
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include "debug.h"
class CStage
{
public:
	CStage();
	bool isRunning;
	void splitStr(const std::string& str, std::vector<int> &cont, char delim = ' ');
	void ReadArrayFromFile(std::string FileName, std::vector<int> &map, char delim = ' ');
	~CStage();
};

