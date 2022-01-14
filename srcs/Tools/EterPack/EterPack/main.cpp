#include "windows.h"
#include "EterIndex.h"
#include "EterPack.h"

BOOL APIENTRY DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved)
{
    switch(dwReason)
    { 
        case DLL_PROCESS_ATTACH:
			return log_init() ? TRUE : FALSE;
            break;
        case DLL_PROCESS_DETACH:
			log_destroy();
            break;
    }

    return TRUE;
}
