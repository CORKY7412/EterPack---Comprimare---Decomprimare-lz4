#include <Windows.h>
#include "EterPack/EterInfo.h"

const UINT32 g_default_index_key[4] = { 0x02B09EB9, 0x0581696F, 0x289B9863, 0x001A1879 };
const UINT32 g_default_pack_key[4] = { 0x04B4B822, 0x1F6EB264, 0x0018EAAE, 0x1CFBF6A6 };

const string g_index_ext = ".eix";
const string g_pack_ext = ".epk";

const STORAGE_TYPE g_storage_type = LZO_COMPRESSION_NO_ENCODING;