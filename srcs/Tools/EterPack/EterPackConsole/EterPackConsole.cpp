#include "stdafx.h"
#include "EterPackHandler.h"
#include "EterPackModule.h"

#include <string>
#include <thread>

#ifdef _DEBUG
#pragma comment(lib, "liblz4_static-d.lib")
#else
#pragma comment(lib, "liblz4_static-r.lib")
#endif

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> files;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			files.push_back(argv[i]);
		}
	}
	else
	{
		return 0:
	}

	if (!files.empty())
	{
		EterPackHandler* handler = new EterPackHandler();

		for (auto file = files.begin(); file != files.end(); ++file)
		{
			string szFile = file->data();

			int mode = 0;

			if (szFile.find(g_index_ext) == szFile.length() - g_index_ext.length())
			{
				mode = MODE_READ;
			}
			else
			{
				mode = MODE_WRITE;
			}

			FindAndReplace(szFile, g_index_ext, "");

			if (MODE_READ == mode)
			{
				handler->ExtractFile(szFile);
			}
			else if (MODE_WRITE == mode)
			{
				handler->PackArchive(szFile);
			}
			else
			{
				return 0;
			}	
		}
	}

	return 0;
}

