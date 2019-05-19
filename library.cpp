#include <windows.h>
#include <iostream>
#include <string>
#include "library.h"
#include "shared_memory.h"

SharedMemory sharedMemoryDllInstance;

void hello()
{
  std::cout << "Hello from DLL" << "\n";
}

extern "C" void dll_func_with_param(std::string from_host)
{
  std::cout << "string from host: " << from_host << "\n";
}

extern "C" void GetInstanceOfSharedMemory(SharedMemory* sharedMemory)
{
  sharedMemory = &sharedMemoryDllInstance;
}

extern "C" BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/)
{
  if (reason == DLL_PROCESS_ATTACH)
  {
    //MessageBoxA(NULL,"test","test",NULL);
    hello();
  }
  return true;
}