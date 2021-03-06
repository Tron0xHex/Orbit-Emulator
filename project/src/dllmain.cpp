#include "pch.h"
#include "Loader.hpp"

// ReSharper disable CppParameterNeverUsed
// ReSharper disable CppParameterMayBeConst
BOOL APIENTRY DllMain(HMODULE hModule,
					  DWORD ulReasonForCall,
					  LPVOID lpReserved)
{
	switch (ulReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
	{
		UbiorbitapiR2Loader::InitConfig();
		UbiorbitapiR2Loader::InitLog();
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	default:;
	}
	return TRUE;
}

// ReSharper restore CppParameterNeverUsed
// ReSharper restore CppParameterMayBeConst
