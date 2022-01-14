#pragma once

#include "EterPackModule.h"
#include "../EterPack/EterPack.h"
#include "../EterPack/EterInfo.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <direct.h>
#include <stdio.h>
#include <thread>

using namespace std;

class EterPackHandler
{
public:
	EterPackHandler();
	~EterPackHandler();

	void ExtractFile(string szCurrentFilePath);
	void PackArchive(string szPackArchive);
	void RoutinePackArchive(string szDirectoryPath);
	void ElaborateIndex();

	void ExtractPacks();

	void ClearAll();

private:
	EINSTANCE pInstanceEix;
	EINSTANCE pInstanceEpk;
	UINT32 iPackCount;
	UINT32 iCurrentPack;
	string szEterPackName;
	string szEterIndexName;
	PLIST pEterIndexItems;
	vector<string> vFileList;

	string szEixName;
	string szEpkName;
};

