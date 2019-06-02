//
// Created by xnorxnor on 19.05.2019.
//

#ifndef DLL_TEST_SHARED_MEMORY_H
#define DLL_TEST_SHARED_MEMORY_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <atomic>

// simple struct with "processed" data, produced by the DLL
struct ResultData
{
  std::string result;
  std::string unit;
  std::vector<std::string> listOfLotNumbers;
  std::string dateTimeStamp;
};

enum class LogLevel
{
  warning,
  info,
  error
};

typedef bool (*CallBackFunctionFromHostToDllPtr)();

typedef std::string (*RequestUserInputFromHostPtr) ();
typedef bool (*RequestDataFromDatabaseWithTimeoutPtr) (const std::string &query);
typedef void (*LogDataFromDllPtr)(LogLevel logLevel, const std::string& logEntry);
typedef void (*ProcessResultDataPtr) ();
typedef void (*StartDllDataProcessingPtr)();

struct SharedMemory
{
  std::string inputFromDll;
  std::string inputFromHost;
  std::vector<std::string> stringsSharedByDllAndHost;
  std::vector<ResultData> listOfResults;

  std::mutex lockDataBaseTable;
  std::map<std::string, std::vector<std::string>> dataBaseTable;
  unsigned int maximumSecondsToWaitForDataBase {5};

  CallBackFunctionFromHostToDllPtr callBackFunctionFromHostToDll {nullptr};
  RequestUserInputFromHostPtr  requestUserInputFromHost {nullptr};
  RequestDataFromDatabaseWithTimeoutPtr requestDataFromDatabaseWithTimeout {nullptr};
  LogDataFromDllPtr logDataFromDll {nullptr};
  ProcessResultDataPtr processResultData {nullptr};
  StartDllDataProcessingPtr startDllDataProcessing {nullptr};
  std::mutex lockResultData;
  std::atomic<bool> allowShutdown {false};
};
#endif //DLL_TEST_SHARED_MEMORY_H
