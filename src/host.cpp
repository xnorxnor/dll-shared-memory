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

typedef void (WINAPI *dll_func_with_param)(std::string);
typedef SharedMemory* (*GetInstanceOfSharedMemory)();

// when using the bcc32c compiler it does not seem possible to remove the _ prefix from export names
// other compilers (gcc, msvc) just create the nice export names
#ifdef __BORLANDC__
  const std::string funcPrefix = "_";
#else
  const std::string funcPrefix = "";
#endif

// TODO: general function to wrap calls to GetProcAddress()
//  TODO: map of function handles and corresponding names
// TODO: Error Handler

int main()
{
  std::cout << "Hello, World!" << std::endl;

  HINSTANCE dllHandle = LoadLibrary("dll-shared-memory.dll");

  if (dllHandle == NULL)
  {
    std::cerr << "Loading of Library failed!";
    return 1;
  }

  dll_func_with_param dllFuncWithParam;
  GetInstanceOfSharedMemory getInstanceOfSharedMemory;
  dllFuncWithParam = (dll_func_with_param) GetProcAddress(dllHandle, (funcPrefix + "dll_func_with_param").c_str());
  getInstanceOfSharedMemory = (GetInstanceOfSharedMemory) GetProcAddress(dllHandle, (funcPrefix + "GetInstanceOfSharedMemory").c_str());

  if (dllFuncWithParam == NULL)
  {
    std::cerr << "Can't get proc address" << "\n";
    return 2;
  }

  if (getInstanceOfSharedMemory == NULL)
  {
    std::cerr << "Can't get proc adress of \"GetInstanceOfSharedMemory\"" << "\n";
    return 3;
  }

  dllFuncWithParam("value from host");

  SharedMemory* sharedMemoryPtr = nullptr;

  sharedMemoryPtr = getInstanceOfSharedMemory();

  sharedMemoryPtr->requestUserInputFromHost = &RequestUserInputFromHost;
  sharedMemoryPtr->logDataFromDll = &LogDataFromDll;
  sharedMemoryPtr->stringsSharedByDllAndHost.push_back("string from host");

//  std::this_thread::sleep_for(std::chrono::seconds(20));

  sharedMemoryPtr->callBackFunctionFromHostToDll();
  FreeLibrary(dllHandle);
  return 0;
}