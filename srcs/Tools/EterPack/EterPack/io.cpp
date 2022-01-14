#include "io.h"

bool FastIO::FileIsEmtpy(string szFilename)
{
    WIN32_FILE_ATTRIBUTE_DATA hFileInfo;

    if(szFilename.empty() || !GetFileAttributesEx(szFilename.c_str(), GetFileExInfoStandard, (void*)&hFileInfo)) return true;

    return (hFileInfo.nFileSizeLow == 0 && hFileInfo.nFileSizeHigh == 0);
}

void FastIO::FileRead(string szFilename, string szMode, void **pOutput, UINT32 *iFileSize)
{
	*pOutput = NULL;
	
	if(szFilename.empty())
	{
		sys_err(__FILE__, __LINE__, "The file name is invalid!");
		return;
	}
	
	FILE *pStreamFile = fopen(szFilename.c_str(), !szMode.empty() ? szMode.c_str() : "rb");
	if(pStreamFile == NULL)
	{
		sys_err(__FILE__, __LINE__, "Impossible to open '%s' (mode '%s')!", szFilename, szMode);
		return;
	}
	
	fseek(pStreamFile, 0, SEEK_END);
	
	*iFileSize = ftell(pStreamFile);
	rewind(pStreamFile);
	
	UINT8 *aRawData = (UINT8 *)malloc(*iFileSize);
	if(aRawData == NULL)
	{
		sys_err(__FILE__, __LINE__, "Impossible to allocate memory (malloc)!");
		return;
	}
	
	if(fread(aRawData, 1, *iFileSize, pStreamFile) != *iFileSize)
	{
		sys_err(__FILE__, __LINE__, "Impossible to read '%s' (mode '%s' len %d)!", szFilename, szMode, iFileSize);
		return;
	}
	
	*pOutput = (void *)aRawData;
	
	fclose(pStreamFile);
}

void FastIO::FileWrite(string szFilename, string szMode, void *pInput, UINT32 iFileSize)
{
	if(szFilename.empty())
	{
		sys_err(__FILE__, __LINE__, "The file name is invalid!");
		return;
	}
	
	FILE *pStreamFile = fopen(szFilename.c_str(), !szMode.empty() ? szMode.c_str() : "wb");
	if(pStreamFile == NULL)
	{
		sys_err(__FILE__, __LINE__, "Impossible to open '%s' (mode '%s')!", szFilename, szMode);
		return;
	}
	
	if(fwrite(pInput, 1, iFileSize, pStreamFile) == NULL)
	{
		sys_err(__FILE__, __LINE__, "Impossible to write '%s' (mode '%s' len %d)!", szFilename, szMode, iFileSize);
		return;
	}
	
	fclose(pStreamFile);
}