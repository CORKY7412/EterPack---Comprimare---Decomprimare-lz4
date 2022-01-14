#pragma once

#include "../EterPack/EterPack.h"
#include "../EterPack/EterInfo.h"

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <sstream>
#include <direct.h>

using namespace std;

void FindAndReplace(string& source, string const& find, string const& replace);
string GetFilteredPath(string szFilePath);
vector<string> SplitString(string str, char delimiter);
bool DirectoryExists(const string& dirName_in);
void CheckAndCreateDir(string fileName);
string GetFileNameFromPath(string szPath);
bool ListFiles(string path, vector<string>& files);
string GetIntelVirtualPath(string szFileVirtualPath);
string GetDiffFromPaths(string szFullPath, string szDiffPath);

