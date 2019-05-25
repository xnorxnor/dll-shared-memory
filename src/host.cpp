//
// Created by xnorxnor on 16.05.2019.
//

#include <windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "host.h"
#include "shared_memory.h"

typedef void (WINAPI *dll_func_with_param)(std::string);
typedef SharedMemory* (*GetInstanceOfSharedMemory)();

#ifdef __BORLANDC__
  const std::string funcPrefix = "_";
#else
  const std::string funcPrefix = "";
#endif

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

  //sharedMemoryPtr->stringsSharedByDllAndHost.push_back("string from host");
//  std::this_thread::sleep_for(std::chrono::seconds(20));

  sharedMemoryPtr->callBackFunctionFromHostToDll();
  FreeLibrary(dllHandle);
  return 0;
}