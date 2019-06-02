//
// Created by xnorxnor on 16.05.2019.
//

#include "host.h"
#include "host_implementation.h"
#include "shared_memory.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>



// when using the bcc32c compiler it does not seem possible to remove the _ prefix from export names
// other compilers (gcc, msvc) just create the nice export names
#ifdef __BORLANDC__
  const std::string funcPrefix = "_";
#else
  const std::string funcPrefix = "";
#endif


int main()
{
  std::cout << "Host starting up, loading DLL" << "\n";

  HINSTANCE dllHandle = LoadLibrary("dll-shared-memory.dll");

  if (dllHandle == NULL)
  {
    std::cerr << "Loading of Library failed!" << "\n";
    return 1;
  }

  GetInstanceOfSharedMemory getInstanceOfSharedMemory;
  getInstanceOfSharedMemory = (GetInstanceOfSharedMemory) GetProcAddress(dllHandle, (funcPrefix + "GetInstanceOfSharedMemory").c_str());

  if (getInstanceOfSharedMemory == NULL)
  {
    std::cerr << "Can't get proc adress of \"GetInstanceOfSharedMemory\"" << "\n";
    return 2;
  }


  // Init shared memory function pointers
  sharedMemoryPtr = getInstanceOfSharedMemory();

  sharedMemoryPtr->requestUserInputFromHost = &RequestUserInputFromHost;
  sharedMemoryPtr->logDataFromDll = &LogDataFromDll;
  sharedMemoryPtr->processResultData = &ProcessResultData;
  sharedMemoryPtr->stringsSharedByDllAndHost.push_back("string from host");

  // Start the DLL thread
  sharedMemoryPtr->startDllDataProcessing();

  std::this_thread::sleep_for(std::chrono::seconds(10));

  sharedMemoryPtr->allowShutdown.store(true);

  std::this_thread::sleep_for(std::chrono::seconds(5));

  FreeLibrary(dllHandle);
  return 0;
}