#ifndef DLL_TEST_LIBRARY_H
#define DLL_TEST_LIBRARY_H

#include "shared_memory.h"
#include <string>
#include <thread>

bool CallBackFunctionFromHostToDll();
void InitSharedMemory();
void StartDllDataProcessing();
std::vector<ResultData> CreateProcessedData();
void ResetResultData(std::vector<ResultData> listOfResults);
void DllDataProcessingThread();

std::thread dllMainThread;

#define DllExport extern "C" __declspec( dllexport )

DllExport SharedMemory* GetInstanceOfSharedMemory(void);

#endif //DLL_TEST_LIBRARY_H