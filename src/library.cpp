#include "library.h"
#include "shared_memory.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// SharedMemory instance in global namespace
SharedMemory sharedMemoryDllInstance;


void InitSharedMemory()
{
  sharedMemoryDllInstance.callBackFunctionFromHostToDll = CallBackFunctionFromHostToDll;
  sharedMemoryDllInstance.startDllDataProcessing = StartDllDataProcessing;
}

bool CallBackFunctionFromHostToDll()
{
  std::cout << "This DLL function was called from Host" << "\n";
  std::cout << "number of Elements in shared vector: [" << sharedMemoryDllInstance.stringsSharedByDllAndHost.size() << "]" << "\n";
  return true;
}

// This is the main function, normally several threads would be started here
// For the sake of simpplicity we only start one thread in the background
// the thraad is joined later when the DLL is unloaded
void StartDllDataProcessing()
{
  dllMainThread = std::move(std::thread([=]() {DllDataProcessingThread(); return 1; }));
}

// Main thread for the dll that runs endlessly until the atomic variable is set accordingly
void DllDataProcessingThread()
{
  sharedMemoryDllInstance.logDataFromDll(LogLevel::info, "Starting data processing");

  while (sharedMemoryDllInstance.allowShutdown.load() == false)
  {
    ResetResultData(CreateProcessedData());
    sharedMemoryDllInstance.processResultData();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    ResetResultData(CreateProcessedData());
    sharedMemoryDllInstance.processResultData();


  }

  sharedMemoryDllInstance.logDataFromDll(LogLevel::info, "Processing complete, shutting down");
}

// Create dummy data to be processed by the host
std::vector<ResultData> CreateProcessedData()
{
  std::vector<ResultData> listOfData;
  ResultData data;

  for (unsigned int i = 0; i < 3; ++i)
  {
    data.listOfLotNumbers.emplace_back("lot 1");
    data.listOfLotNumbers.emplace_back("lot 2");
    data.result = "result " + std::to_string(i);
    data.unit = "mmol/L";
    data.dateTimeStamp = "14-09-2018";

    listOfData.emplace_back(data);
  }

  return listOfData;
}

// Clear vector of ResultData items and lock the access during the operation
void ResetResultData(std::vector<ResultData> listOfResults)
{
  std::lock_guard<std::mutex> guard(sharedMemoryDllInstance.lockResultData);
  sharedMemoryDllInstance.listOfResults = listOfResults;
}

// Let the host retrieve the address of the SharedMemory instance
SharedMemory* GetInstanceOfSharedMemory(void)
{
  return &sharedMemoryDllInstance;
}


extern "C" BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/)
{
  if (reason == DLL_PROCESS_ATTACH)
  {
    InitSharedMemory();
  }

  if (reason == DLL_PROCESS_DETACH)
  {
    dllMainThread.join();
  }
  return true;
}