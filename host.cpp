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
typedef void (*GetInstanceOfSharedMemory)(SharedMemory*);

int main()
{
  std::cout << "Hello, World!" << std::endl;

  HINSTANCE dllHandle = LoadLibrary("dll_test.dll");

  if (dllHandle == NULL)
  {
    std::cerr << "Loading of Library failed!";
    return 1;
  }

  dll_func_with_param dllFuncWithParam;
  GetInstanceOfSharedMemory getInstanceOfSharedMemory;
  dllFuncWithParam = (dll_func_with_param) GetProcAddress(dllHandle, "dll_func_with_param");
  getInstanceOfSharedMemory = (GetInstanceOfSharedMemory) GetProcAddress(dllHandle, "GetInstanceOfSharedMemory");

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

  getInstanceOfSharedMemory(sharedMemoryPtr);

  sharedMemoryPtr->stringsSharedByDllAndHost.push_back("string from host");
//  std::this_thread::sleep_for(std::chrono::seconds(20));
  FreeLibrary(dllHandle);
  return 0;
}