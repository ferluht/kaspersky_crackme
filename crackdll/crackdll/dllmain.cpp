#include "stdafx.h"
#include <stdio.h>

unsigned int hash[20] = {};
char mail[25] = "sample@gmail.com";
char pass[33] = "00000000000000000000000000000000";


DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;
void __stdcall CallFunction(void);
int __stdcall CallMainFunction(int argv, char **argc);
int __stdcall CallLitEndFunction(int& inp);

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hModule = hModule;
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, &MyThread, NULL, NULL, &g_threadID);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}


DWORD WINAPI MyThread(LPVOID)
{
	char *argc[2] = { pass, mail };
	while (true)
	{
		if (GetAsyncKeyState(VK_F3) & 1) //Set F3 as our hotkey
		{
			for (int i = 0; i < 20; i++) {
				printf("%u ", hash[i]);
			}
			printf("\n");

			int a = 1213029;

			//CallLitEndFunction(a);
			CallMainFunction(0, argc);

			for (int i = 0; i < 20; i++) {
				printf("%u ", hash[i]);
			}
			printf("\n");
		}
		else if (GetAsyncKeyState(VK_F4) & 1)
			break;
		Sleep(100);
	}
	FreeLibraryAndExitThread(g_hModule, 0);
	return 0;
}

int __stdcall CallLitEndFunction(int& inp)
{
	typedef int(__stdcall *pFunctionAddress)(int&);
	pFunctionAddress pWinFunction = (pFunctionAddress)(0x00401960); //Our new address
	return pWinFunction(inp); //Call it with 1 to win the game
}

int __stdcall CallMainFunction(int argv, char **argc)
{
	typedef int(__stdcall *pFunctionAddress)(int, char**);
	pFunctionAddress pWinFunction = (pFunctionAddress)(0x00401D40); //Our new address
	return pWinFunction(argv, argc); //Call it with 1 to win the game
}
