#include "library.h"
#include <windows.h>
#include <iostream>

void hello()
{
  std::cout << "Hello from DLL" << "\n";
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