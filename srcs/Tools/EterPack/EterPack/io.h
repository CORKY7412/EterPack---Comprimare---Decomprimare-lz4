#include <Windows.h>
#include <fstream>
#include "log.h"

using namespace std;

namespace FastIO {
	bool FileIsEmtpy(string szFilename);
	void FileRead(string szFilename, string szMode, void **pOutput, UINT32 *iFileSize);
	void FileWrite(string szFilename, string szMode, void *pInput, UINT32 iFileSize);
}