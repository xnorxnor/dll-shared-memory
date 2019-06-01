//
// Created by xnorxnor on 27.05.2019.
//

#include "host_implementation.h"
#include "shared_memory.h"
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

SharedMemory* sharedMemoryPtr = nullptr;


void ProcessResultData()
{
  std::lock_guard<std::mutex> guard(sharedMemoryPtr->lockResultData);

  for (auto &result : sharedMemoryPtr->listOfResults)
  {
    std::string resultAsString;

    resultAsString = result.dateTimeStamp + ", " + result.result + "(" + result.unit + ")";

    std::cout << "Processed result [" << resultAsString << "]";
  }
}


void LogDataFromDll(LogLevel logLevel, const std::string &logEntry)
{
  std::string prefix;

  switch (logLevel)
  {
    case LogLevel::error:
      prefix = "[error] ";
      break;
    case LogLevel::info:
      prefix = "[info] ";
      break;
    case LogLevel::warning:
      prefix = "[warn] ";
      break;
  }

  std::cout << "Log: " << GenerateTimeStamp() << prefix << logEntry << "\n";
}

std::string GenerateUserInputData()
{
  return "user input: [ " + GenerateTimeStamp() + "]";
}

std::string GenerateTimeStamp()
{
  auto t = time(nullptr);
  auto tm = *localtime(&t);

  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

  return oss.str();
}

std::string RequestUserInputFromHost()
{
  // normally, a user dialog would show up here
  // we generate some fake user input data here
  return GenerateUserInputData();
}

