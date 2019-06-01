//
// Created by xnorxnor on 28.05.2019.
//

#ifndef DLL_TEST_HOST_IMPLEMENTATION_H
#define DLL_TEST_HOST_IMPLEMENTATION_H

#include "shared_memory.h"
#include <string>

extern SharedMemory* sharedMemoryPtr;

void LogDataFromDll(LogLevel logLevel, const std::string& logEntry);
std::string GenerateTimeStamp();
std::string GenerateUserInputData();
std::string RequestUserInputFromHost();
void ProcessResultData();
std::string GenerateTimeStamp();

#endif //DLL_TEST_HOST_IMPLEMENTATION_H
