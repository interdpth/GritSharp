// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "../libgrit/grit.h"
#include <string>
#include <windows.h>
#include <shellapi.h>
char path[5098];
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
extern "C" {
    __declspec(dllexport) GritRec* InitGrit(void) {

        //char radiostring[3][32] = { "-Ah 32 -Aw 32","-Ah 64 -Aw 32","-Ah 32 -Aw 64" };

           
        return NULL;
    }




    __declspec(dllexport) void SetSource(GritRec* ret, const char* tstring)
    {
       // sprintf_s(path, 4096, "%s", tstring);
     //   ret->srcPath = path;
      //  printf("Setting soruce. %s", ret->srcPath);
       
    }

    //-gb -gB 16 -ftbin
    __declspec(dllexport) void SetBitmapMode(GritRec* ret) {

       // ret->gfxMode = GRIT_GFX_BMP;
       // ret->gfxBpp = 16;
    }
	GritInterface* newInterface = NULL;

	LPSTR* CommandLineToArgvA(LPSTR lpCmdLine, INT* pNumArgs)
	{
		int retval;
		retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, NULL, 0);
		if (!SUCCEEDED(retval))
			return NULL;

		LPWSTR lpWideCharStr = (LPWSTR)malloc(retval * sizeof(WCHAR));
		if (lpWideCharStr == NULL)
			return NULL;

		retval = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, lpCmdLine, -1, lpWideCharStr, retval);
		if (!SUCCEEDED(retval))
		{
			free(lpWideCharStr);
			return NULL;
		}

		int numArgs;
		LPWSTR* args;
		args = CommandLineToArgvW(lpWideCharStr, &numArgs);
		free(lpWideCharStr);
		if (args == NULL)
			return NULL;

		int storage = numArgs * sizeof(LPSTR);
		for (int i = 0; i < numArgs; ++i)
		{
			BOOL lpUsedDefaultChar = FALSE;
			retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, NULL, 0, NULL, &lpUsedDefaultChar);
			if (!SUCCEEDED(retval))
			{
				LocalFree(args);
				return NULL;
			}

			storage += retval;
		}

		LPSTR* result = (LPSTR*)LocalAlloc(LMEM_FIXED, storage);
		if (result == NULL)
		{
			LocalFree(args);
			return NULL;
		}

		int bufLen = storage - numArgs * sizeof(LPSTR);
		LPSTR buffer = ((LPSTR)result) + numArgs * sizeof(LPSTR);
		for (int i = 0; i < numArgs; ++i)
		{
			_ASSERT(bufLen > 0);
			BOOL lpUsedDefaultChar = FALSE;
			retval = WideCharToMultiByte(CP_ACP, 0, args[i], -1, buffer, bufLen, NULL, &lpUsedDefaultChar);
			if (!SUCCEEDED(retval))
			{
				LocalFree(result);
				LocalFree(args);
				return NULL;
			}

			result[i] = buffer;
			buffer += retval;
			bufLen -= retval;
		}

		LocalFree(args);

		*pNumArgs = numArgs;
		return result;
	}
	GritRec* rec = NULL;
    __declspec(dllexport) GritRec* Convert(char* tstring) {
    
		if(newInterface  == NULL) newInterface = new GritInterface(NULL);
        char param[1024];
		int numargs = 4;
        sprintf_s(param, 1024, "%s %s -gb -gB 16", tstring, tstring);
		char** params = CommandLineToArgvA(param, &numargs);
		//char radiostring[3][32] = { "-Ah 32 -Aw 32","-Ah 64 -Aw 32","-Ah 32 -Aw 64" };
			
		if (rec != NULL) delete rec;

		rec = newInterface->run_main(numargs, params);
		
		LocalFree(params);
		return rec;
    }


    __declspec(dllexport) unsigned char* GetBitmap(GritRec* src)
    {
		return src->_gfxRec.data;
    }
    __declspec(dllexport) long GetBitmapLen(GritRec* src)
    {
        return src->areaRight * src->areaBottom;
    }
}