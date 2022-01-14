#include "stdafx.h"
#include "EterPackModule.h"

EINSTANCE LoadEterIndex(string szFilename, int iMode)
{
	sys_log(0, "====================== NEW INDEX CLASS ======================");

	EterIndex *pEixClass = new EterIndex(szFilename);

	if (!pEixClass) return 0;
	if (iMode == MODE_READ)
	{
		if (!pEixClass->LoadFile())
		{
			delete pEixClass;
			sys_log(1, "FAILED TO LOAD FILE %s", szFilename);
			return 0;
		}
	}

	sys_log(0, "ISTANCE AT 0x%p", pEixClass);
	sys_log(0, "ABSOLUTE PATH: %s", szFilename);

	return (EINSTANCE)pEixClass;
}

EINSTANCE LoadEterPack(string szFilename, int iMode)
{
	EterPack *pEpkClass = new EterPack(szFilename, iMode == MODE_READ);

	sys_log(0, "====================== NEW PACK CLASS ======================");
	sys_log(0, "ISTANCE AT 0x%p", pEpkClass);
	sys_log(0, "ABSOLUTE PATH: %s", szFilename);

	return (EINSTANCE)pEpkClass;
}

PLIST GetFilesList(EINSTANCE pInstance)
{
	return (pInstance != 0) ? ((EterIndex *)pInstance)->GetAllFiles() : 0;
}

UINT32 GetFileCount(EINSTANCE pInstance)
{
	return (pInstance != 0) ? ((EterIndex *)pInstance)->GetFileCount() : 0;
}

void InitPack(EINSTANCE pInstance, UINT32 iFileCount)
{
	if (pInstance == 0) return;

	((EterIndex *)pInstance)->InitPack(iFileCount);
}

void PutFile(EINSTANCE pInstance, const char *szFilename, enum STORAGE_TYPE eType, UINT32 iFileSize, UINT32 iHashCRC32)
{
	if (pInstance == 0) return;

	((EterIndex *)pInstance)->PutFile(szFilename, eType, iFileSize, iHashCRC32);
}

void WritePack(EINSTANCE pInstance)
{
	if (pInstance == 0) return;

	((EterIndex *)pInstance)->WritePack();
}

void FreeEterIndex(EINSTANCE pInstance)
{
	if (pInstance == 0) return;

	delete ((EterIndex *)pInstance);
}

UINT8 *GetFileData(EINSTANCE pInstance, EterIndexItem *pEixItem)
{
	return (pInstance != 0) ? ((EterPack *)pInstance)->GetStoredData(pEixItem, true) : 0;
}

UINT32 GetDataSize(EINSTANCE pInstance)
{
	return (pInstance != 0) ? ((EterPack *)pInstance)->GetStoredSize() : 0;
}

bool PutFileData(EINSTANCE pInstance, const char *szFilename, enum STORAGE_TYPE eType, UINT32 *iOutSize, UINT32 *iHashCRC32)
{
	return (pInstance != 0) ? ((EterPack *)pInstance)->PutPack(szFilename, eType, iOutSize, iHashCRC32) : false;
}

void FreeEterPack(EINSTANCE pInstance)
{
	if (pInstance == 0) return;

	delete ((EterPack *)pInstance);
}
