//
// Created by xnorxnor on 19.05.2019.
//

#ifndef DLL_TEST_SHARED_MEMORY_H
#define DLL_TEST_SHARED_MEMORY_H

#include <string>
#include <vector>

typedef bool (*CallBackFunctionFromHostToDllPtr)();

struct SharedMemory
{
  std::string inputFromDll;
  std::string inputFromHost;
  std::vector<std::string> stringsSharedByDllAndHost;
  CallBackFunctionFromHostToDllPtr callBackFunctionFromHostToDll {nullptr};
};
#endif //DLL_TEST_SHARED_MEMORY_H
