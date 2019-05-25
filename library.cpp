#include <windows.h>
#include <iostream>
#include <string>
#include "library.h"
#include "shared_memory.h"

SharedMemory sharedMemoryDllInstance;

void InitSharedMemory();

void hello()
{
  std::cout << "Hello from DLL" << "\n";
}

void dll_func_with_param (std::string from_host)
//extern "C" void dll_func_with_param(std::string from_host)
{
  std::cout << "string from host: " << from_host << "\n";
}

void InitSharedMemory()
{
  sharedMemoryDllInstance.callBackFunctionFromHostToDll = CallBackFunctionFromHostToDll;
  sharedMemoryDllInstance.stringsSharedByDllAndHost.reserve(100);
  sharedMemoryDllInstance.stringsSharedByDllAndHost.resize(100);
}

bool CallBackFunctionFromHostToDll()
{
  std::cout << "This DLL function was called from Host" << "\n";
  return true;
}

void GetInstanceOfSharedMemory(SharedMemory* sharedMemory)
{
  sharedMemory = &sharedMemoryDllInstance;
}

extern "C" BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/)
{
  if (reason == DLL_PROCESS_ATTACH)
  {
    //MessageBoxA(NULL,"test","test",NULL);
    hello();
    InitSharedMemory();
  }
  return true;
}