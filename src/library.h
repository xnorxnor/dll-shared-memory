#ifndef DLL_TEST_LIBRARY_H
#define DLL_TEST_LIBRARY_H

#include "shared_memory.h"
#include <string>

void hello();
bool CallBackFunctionFromHostToDll();
void InitSharedMemory();
void StartDllDataProcessing();
std::vector<ResultData> CreateProcessedData();
void ResetResultData(std::vector<ResultData> listOfResults);

#define DllExport extern "C" __declspec( dllexport )

DllExport void dll_func_with_param (std::string from_host);
//DllExport void GetInstanceOfSharedMemory(SharedMemory** sharedMemory);
DllExport SharedMemory* GetInstanceOfSharedMemory(void);

#endif //DLL_TEST_LIBRARY_H