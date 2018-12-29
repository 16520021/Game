#include "Stage.h"


CStage::CStage()
{
	isRunning = false;
}

void CStage::splitStr(const std::string & str, std::vector<int>& cont, char delim)
{
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		cont.push_back(stoi(token));
	}
}

void CStage::ReadArrayFromFile(std::string FileName, std::vector<int>& map, char delim)
{
	std::ifstream inputFile;
	std::string strs;
	inputFile.open(FileName);
	if (!inputFile)
		DebugOut(L"file open fail");
	while (!inputFile.eof())
	{
		inputFile >> strs;
		splitStr(strs, map, delim);
	}
	inputFile.close();
}


CStage::~CStage()
{
}
