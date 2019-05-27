//
// Created by xnorxnor on 19.05.2019.
//

#ifndef DLL_TEST_SHARED_MEMORY_H
#define DLL_TEST_SHARED_MEMORY_H

#include <string>
#include <vector>
#include <map>

// simple struct with "processed" data, produced by the DLL
struct ProcessedData
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
typedef bool (*RequestDataFromDatabaseWithTimeoutPtr) (const std::string &query, std::map<std::string, std::vector<std::string>> &dataBaseTable, unsigned int maximumSecondsToWait);
typedef void (*LogDataFromDllPtr)(LogLevel logLevel, std::string& logEntry);
typedef void (*SendProcessedDataToHostPtr) (const std::vector<ProcessedData>& listOfProcessedDataItems);

struct SharedMemory
{
  std::string inputFromDll;
  std::string inputFromHost;
  std::vector<std::string> stringsSharedByDllAndHost;
  CallBackFunctionFromHostToDllPtr callBackFunctionFromHostToDll {nullptr};
  RequestUserInputFromHostPtr  requestUserInputFromHost {nullptr};
  RequestDataFromDatabaseWithTimeoutPtr requestDataFromDatabaseWithTimeout {nullptr};
  LogDataFromDllPtr logDataFromDll {nullptr};
  SendProcessedDataToHostPtr sendProcessedDataToHost {nullptr};
};
#endif //DLL_TEST_SHARED_MEMORY_H
