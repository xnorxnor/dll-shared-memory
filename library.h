#ifndef DLL_TEST_LIBRARY_H
#define DLL_TEST_LIBRARY_H

#include "shared_memory.h"
#include <string>

void hello();
bool CallBackFunctionFromHostToDll();
void InitSharedMemory();

#define DllExport extern "C" __declspec( dllexport )
//#define DllExport __declspec( dllexport )

//#pragma comment(linker, "/export:dll_func_with_param=_dll_func_with_param")
DllExport void dll_func_with_param (std::string from_host);
//#pragma comment(linker, "/export:GetInstanceOfSharedMemory=_GetInstanceOfSharedMemory")
DllExport void GetInstanceOfSharedMemory(SharedMemory* sharedMemory);

#endif //DLL_TEST_LIBRARY_H