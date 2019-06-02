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
#include <future>
#include <time.h>

#include <cmath>
#include <functional>

SharedMemory* sharedMemoryPtr = nullptr;
bool runIntoTimeoutOnDbQuery = false;

void ProcessResultData()
{
  std::lock_guard<std::mutex> guard(sharedMemoryPtr->lockResultData);

  for (auto &result : sharedMemoryPtr->listOfResults)
  {
    std::string resultAsString;

    resultAsString = result.dateTimeStamp + ", " + result.result + "(" + result.unit + ")";

    std::cout << "Processed result [" << resultAsString << "]\n";
  }
}

// every second time, the database query will run into a timeout
// here we simply simulate this with a sleep :-)
void GetDatabaseContent(std::string query)
{
  sharedMemoryPtr->dataBaseTable.emplace("col1", std::vector<std::string> {"elem11", "elem12"});
  sharedMemoryPtr->dataBaseTable.emplace("col2", std::vector<std::string> {"elem21", "elem22"});

  if (runIntoTimeoutOnDbQuery)
    std::this_thread::sleep_for(std::chrono::seconds(sharedMemoryPtr->maximumSecondsToWaitForDataBase + 1));

  runIntoTimeoutOnDbQuery = !runIntoTimeoutOnDbQuery;
}

// Start the "query" in an extra thread
// We will wait for the specified timeout and return to the caller
bool RequestDataFromDatabaseWithTimeout (const std::string &query)
{
  std::lock_guard<std::mutex> guard(sharedMemoryPtr->lockDataBaseTable);
  sharedMemoryPtr->dataBaseTable.clear();

  std::cout << "Starting DB query for query [" << query << "]" << "\n";

  std::packaged_task<void(std::string )> task(GetDatabaseContent);
  auto future = task.get_future();
  std::thread thr(std::move(task), query);
  if (future.wait_for(std::chrono::seconds(sharedMemoryPtr->maximumSecondsToWaitForDataBase)) != std::future_status::timeout)
  {
    future.get(); 
    thr.join(); // let the thread finish
    return true;
  }
  else
  {
    thr.detach(); // we leave the thread still running
    return false;
  }
}

void LogDataFromDll(LogLevel logLevel, const std::string &logEntry)
{
  std::string prefix;

  switch (logLevel)
  {
    case LogLevel::error:
      prefix = " [error] ";
      break;
    case LogLevel::info:
      prefix = " [info] ";
      break;
    case LogLevel::warning:
      prefix = " [warn] ";
      break;
  }

  std::cout << "Log: " << GenerateTimeStamp() << prefix << logEntry << "\n";
}

std::string GenerateUserInputData()
{
  return "user input: [ " + GenerateTimeStamp() + "]";
}

// use localtime_s when compiling with msvc
std::string GenerateTimeStamp()
{
  auto t = time(nullptr);
  #ifdef _MSC_VER
    struct tm buf;
    localtime_s(&buf, &t);
  #else
   auto buf = *localtime(&t);
  #endif
  std::ostringstream oss;
  oss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");

  return oss.str();
}

std::string RequestUserInputFromHost()
{
  // normally, a user dialog would show up where a user could input data
  // we generate some fake user input data here
  return GenerateUserInputData();
}

