#include "stdafx.h"
#include "EterPackHandler.h"

#include <thread>

//#define MULTITHREAD_EXTRACT

EterPackHandler::EterPackHandler()
{
}


EterPackHandler::~EterPackHandler()
{
}

void EterPackHandler::ClearAll()
{
	pInstanceEix = 0;
	pInstanceEpk = 0;

	iPackCount = 0;
	iCurrentPack = 0;
	pEterIndexItems = 0;

	szEterPackName.clear();
	szEterIndexName.clear();
	szEixName.clear();
	szEpkName.clear();

	if (pInstanceEix)
	{
		FreeEterIndex(pInstanceEix);
	}

	if (pInstanceEpk)
	{
		FreeEterPack(pInstanceEpk);
	}
}

void EterPackHandler::ExtractFile(string szCurrentFilePath)
{
	ClearAll();

	szEterIndexName = szCurrentFilePath + g_index_ext;
	szEterPackName = szCurrentFilePath + g_pack_ext;

	pInstanceEix = LoadEterIndex(szEterIndexName, MODE_READ);

	ElaborateIndex();
}

void EterPackHandler::PackArchive(string szDirectoryPath)
{
	ClearAll();

	if (szDirectoryPath.find_last_of("\\") != szDirectoryPath.length() - 1)
	{
		szDirectoryPath.append("\\");
	}

	szEixName = szDirectoryPath.substr(0, szDirectoryPath.find_last_of("\\")).append(g_index_ext);
	szEpkName = szDirectoryPath.substr(0, szDirectoryPath.find_last_of("\\")).append(g_pack_ext);

	// Remove files if already exists
	if (ifstream(szEixName))
	{
		remove(szEixName.c_str());
	}

	if (ifstream(szEpkName))
	{
		remove(szEpkName.c_str());
	}

	// Load EterIndex and EterPack
	pInstanceEix = LoadEterIndex(szEixName, MODE_WRITE);
	pInstanceEpk = LoadEterPack(szEpkName, MODE_WRITE);

	if (!pInstanceEix || !pInstanceEpk)
	{
		return;
	}

	ListFiles(szDirectoryPath, vFileList);

	iPackCount = vFileList.size();

	if (iPackCount > 0)
	{
		iCurrentPack = 0;

		InitPack(pInstanceEix, iPackCount);

		RoutinePackArchive(szDirectoryPath);
	}
}

void EterPackHandler::RoutinePackArchive(string szDirectoryPath)
{
	if (!pInstanceEix || !pInstanceEpk)
	{
		return;
	}

	while (iCurrentPack < iPackCount)
	{
		if (!pInstanceEpk)
		{
			pInstanceEpk = LoadEterPack(szEterPackName, MODE_READ);
		}

		if (pInstanceEpk == NULL)
		{
			exit(0);
		}

		if (szDirectoryPath == "" || vFileList.size() == 0 || !pInstanceEix || !pInstanceEpk)
		{
			return;
		}

		UINT32 iOutSize = 0, iHashCRC32 = 0;

		string szFileVirtualPath = GetDiffFromPaths(vFileList.at(iCurrentPack).data(), szDirectoryPath);

		printf("Adding: %s\n", szFileVirtualPath.c_str());

		PutFileData(pInstanceEpk, vFileList.at(iCurrentPack++).data(), g_storage_type, &iOutSize, &iHashCRC32);
		PutFile(pInstanceEix, GetIntelVirtualPath(szFileVirtualPath).data(), g_storage_type, iOutSize, iHashCRC32);
	}

	WritePack(pInstanceEix);

	ClearAll();
}

void EterPackHandler::ElaborateIndex()
{
	if (!pInstanceEix)
	{
		return;
	}

	pEterIndexItems = GetFilesList(pInstanceEix);
	iPackCount = GetFileCount(pInstanceEix);
	iCurrentPack = 0;

	if (iPackCount == 0 || !pEterIndexItems)
	{
		return;
	}

	ExtractPacks();
}

void ExtractSinglePack(string szEterPackName, EterIndexItem* pEterIndexItem, UINT32 pInstanceEix, UINT32 pInstanceEpk)
{
	UINT8 *pEterPackData = GetFileData(pInstanceEpk, pEterIndexItem);
	UINT32 pEterPackSize = GetDataSize(pInstanceEpk);
	string szFilePath, szMainDirectory;

	if (pEterPackData == NULL && pEterPackSize > 0)
	{
		exit(0);
	}

	szMainDirectory = szEterPackName.substr(0, szEterPackName.length() - g_pack_ext.length());

	szFilePath += szMainDirectory + "\\" + GetFilteredPath(pEterIndexItem->VirtualPath);
	CheckAndCreateDir(szFilePath);

	printf("Extract %s \n", pEterIndexItem->VirtualPath);

	FastIO::FileWrite(szFilePath, "wb", pEterPackData, pEterPackSize);
}

void EterPackHandler::ExtractPacks()
{
	if (pInstanceEix && pEterIndexItems)
	{
		pInstanceEpk = LoadEterPack(szEterPackName, MODE_READ);

		if (pInstanceEpk == NULL)
		{
			exit(0);
		}

#ifndef MULTITHREAD_EXTRACT
		while (iCurrentPack < iPackCount)
		{
			ExtractSinglePack(szEterPackName, pEterIndexItems[iCurrentPack++], pInstanceEix, pInstanceEpk);
		}
#else
		thread *threads = new thread[iPackCount];

		for (int i = 0; i < iPackCount; i++)
		{
			threads[i] = thread(ExtractSinglePack, szEterPackName, pEterIndexItems[i], pInstanceEix, pInstanceEpk);
		}

		for (int i = 0; i < iPackCount; i++)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}
#endif
	}
}
