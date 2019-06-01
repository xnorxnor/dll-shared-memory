#include "library.h"
#include "shared_memory.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

// SharedMemory instance in global namespace
SharedMemory sharedMemoryDllInstance;


void hello()
{
  std::cout << "Hello from DLL" << "\n";
}

void dll_func_with_param (std::string from_host)
{
  std::cout << "string from host: " << from_host << "\n";
}

void InitSharedMemory()
{
  sharedMemoryDllInstance.callBackFunctionFromHostToDll = CallBackFunctionFromHostToDll;
  sharedMemoryDllInstance.startDllDataProcessing = StartDllDataProcessing;
  //sharedMemoryDllInstance.stringsSharedByDllAndHost.reserve(100);
}

bool CallBackFunctionFromHostToDll()
{
  std::cout << "This DLL function was called from Host" << "\n";
  std::cout << "number of Elements in shared vector: [" << sharedMemoryDllInstance.stringsSharedByDllAndHost.size() << "]" << "\n";
  return true;
}

// This is the main function, normally this would run in an extra thread
// and functions would be called after certain events are triggered
void StartDllDataProcessing()
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

void ResetResultData(std::vector<ResultData> listOfResults)
{
  std::lock_guard<std::mutex> guard(sharedMemoryDllInstance.lockResultData);
  sharedMemoryDllInstance.listOfResults = listOfResults;
}

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
    // clean up
  }
  return true;
}