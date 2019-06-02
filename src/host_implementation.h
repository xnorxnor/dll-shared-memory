//
// Created by xnorxnor on 28.05.2019.
//

#ifndef DLL_TEST_HOST_IMPLEMENTATION_H
#define DLL_TEST_HOST_IMPLEMENTATION_H

#include "shared_memory.h"
#include <string>

extern SharedMemory* sharedMemoryPtr;
extern bool runIntoTimeoutOnDbQuery;

void LogDataFromDll(LogLevel logLevel, const std::string& logEntry);
std::string GenerateTimeStamp();
std::string GenerateUserInputData();
std::string RequestUserInputFromHost();
void ProcessResultData();
std::string GenerateTimeStamp();
bool RequestDataFromDatabaseWithTimeout (const std::string &query);

#endif //DLL_TEST_HOST_IMPLEMENTATION_H
