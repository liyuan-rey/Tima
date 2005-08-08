#pragma once

//

#ifndef TCHK_API
	#define TCHK_API		__declspec(dllimport)
#else
	#undef TCHK_API
	#define TCHK_API		__declspec(dllexport)
#endif

//

TCHK_API BOOL WINAPI InstallTrayClockHook(HWND hWndHook);
TCHK_API BOOL WINAPI UninstallTrayClockHook();
