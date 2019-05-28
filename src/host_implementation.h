//
// Created by xnorxnor on 28.05.2019.
//

#ifndef DLL_TEST_HOST_IMPLEMENTATION_H
#define DLL_TEST_HOST_IMPLEMENTATION_H

#include "shared_memory.h"
#include <string>

void LogDataFromDll(LogLevel logLevel, const std::string& logEntry);
std::string GenerateUserInputData();
std::string RequestUserInputFromHost();

#endif //DLL_TEST_HOST_IMPLEMENTATION_H
