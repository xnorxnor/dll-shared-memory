#include "library.h"
#include <windows.h>
#include <iostream>

void hello()
{
  //AllocConsole();
  //freopen("CONOUT$", "w", stdout);
  std::cout << "Hello from DLL" << "\n";
}

//BOOL APIENTRY DllMain ( HMODULE hModule, DWORD reason, LPVOID lpReserved ) {
extern "C" BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/)
{
//bool __stdcall DllMain(HMODULE /*module*/, DWORD reason, LPVOID /*reserved*/) {
  if (reason == DLL_PROCESS_ATTACH)
  {
    //MessageBoxA(NULL,"test","test",NULL);
    hello();
  }
  return true;
}