#pragma once

#include "../EterPack/EterPack.h"
#include "../EterPack/EterInfo.h"


#define PLIST EterIndexItem **
#define EINSTANCE UINT32
#define MODE_READ  0
#define MODE_WRITE 1

EINSTANCE LoadEterIndex(string szFilename, int iMode);
EINSTANCE LoadEterPack(string szFilename, int iMode);
PLIST GetFilesList(EINSTANCE pInstance);
UINT32 GetFileCount(EINSTANCE pInstance);
void InitPack(EINSTANCE pInstance, UINT32 iFileCount);
void PutFile(EINSTANCE pInstance, const char *szFilename, enum STORAGE_TYPE eType, UINT32 iFileSize, UINT32 iHashCRC32);
void WritePack(EINSTANCE pInstance);
void FreeEterIndex(EINSTANCE pInstance);
UINT8 *GetFileData(EINSTANCE pInstance, EterIndexItem *pEixItem);
UINT32 GetDataSize(EINSTANCE pInstance);
bool PutFileData(EINSTANCE pInstance, const char *szFilename, enum STORAGE_TYPE eType, UINT32 *iOutSize, UINT32 *iHashCRC32);
void FreeEterPack(EINSTANCE pInstance);

