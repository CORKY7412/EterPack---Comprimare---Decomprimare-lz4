#include "stdafx.h"
#include "Utils.h"

void FindAndReplace(string& source, string const& find, string const& replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

string GetFilteredPath(string szFilePath)
{
	FindAndReplace(szFilePath, "/", "\\");
	FindAndReplace(szFilePath, "d:\\", "");

	return szFilePath;
}

vector<string> SplitString(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str);
	string tok;

	while (getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}

bool DirectoryExists(const string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}

	return false;
}

void CheckAndCreateDir(string fileName)
{
	FindAndReplace(fileName, "/", "\\");

	string tPath, dir = fileName.substr(0, fileName.find_last_of("\\"));

	if (!dir.find("\\"))
	{
		return;
	}

	vector<string> dirList = SplitString(dir, '\\');
	for (auto part = dirList.begin(); part != dirList.end(); ++part)
	{
		if (part->compare("d:") != 0)
		{
			tPath.append((*part)).append("\\");

			if (!DirectoryExists(tPath))
			{
				mkdir(tPath.c_str());
			}
		}
	}
}

string GetFileNameFromPath(string szPath)
{
	if (!szPath.find("\\"))
	{
		return szPath;
	}

	if (szPath.find_last_of("\\") == szPath.length() - 1)
	{
		szPath = szPath.substr(szPath.find_last_of("\\") + 1, szPath.length() - 1);
	}

	return szPath.substr(szPath.find_last_of("\\") + 1);
}

bool ListFiles(string directoryPath, vector<string>& files)
{
	if (directoryPath.find_last_of("\\") == directoryPath.length() - 1)
	{
		directoryPath = directoryPath.substr(0, directoryPath.length() - 1);
	}

	std::wstring path(directoryPath.begin(), directoryPath.end());

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;
	wstring spec;
	stack<wstring> directories;

	directories.push(path);
	files.clear();

	while (!directories.empty()) {
		path = directories.top();
		spec = path + L"\\*";
		directories.pop();

		hFind = FindFirstFile(spec.c_str(), &ffd);
		if (hFind == INVALID_HANDLE_VALUE) {
			return false;
		}

		do {
			if (wcscmp(ffd.cFileName, L".") != 0 &&
				wcscmp(ffd.cFileName, L"..") != 0) {
				if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					directories.push(path + L"\\" + ffd.cFileName);
				}
				else {
					std::wstring ws = ffd.cFileName;
					std::string file(ws.begin(), ws.end());
					std::string dir(path.begin(), path.end());

					char buffer[MAX_PATH];
					snprintf(buffer, MAX_PATH, "%s\\%s", dir.c_str(), file.c_str());

					files.push_back(buffer);
				}
			}
		} while (FindNextFile(hFind, &ffd) != 0);

		if (GetLastError() != ERROR_NO_MORE_FILES) {
			FindClose(hFind);
			return false;
		}

		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	return true;
}

string GetIntelVirtualPath(string szFileVirtualPath)
{
	FindAndReplace(szFileVirtualPath, "\\", "/");

	if (szFileVirtualPath.substr(0, string("ymir work").length()) == "ymir work")
	{
		szFileVirtualPath.insert(0, "d:/");
	}

#ifdef ETER_NEXUS_UNIVERSAL_ELEMENTS
	if (szFileVirtualPath.left(QString("universalelements work").length()) == "universalelements work")
		szFileVirtualPath.insert(0, "d:/");
#endif

	return szFileVirtualPath;
}

string GetDiffFromPaths(string szFullPath, string szDiffPath)
{
	if (szDiffPath.length() >= szFullPath.length()) return szFullPath;
	//if(szDiffPath.lastIndexOf("\\") >= szFullPath.length()) return szFullPath;

	return szFullPath.substr(szDiffPath.length());
	//return szFullPath.right(szFullPath.length()-szDiffPath.lastIndexOf("\\")-1);
}
