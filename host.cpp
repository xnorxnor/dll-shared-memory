//
// Created by xnorxnor on 16.05.2019.
//

#include "host.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>

int main()
{
  std::cout << "Hello, World!" << std::endl;

  HINSTANCE dllHandle = LoadLibrary("dll_test.dll");

  if (dllHandle == NULL)
    std::cerr << "Loading of Library failed!";

//  std::this_thread::sleep_for(std::chrono::seconds(20));
  FreeLibrary(dllHandle);
  return 0;
}