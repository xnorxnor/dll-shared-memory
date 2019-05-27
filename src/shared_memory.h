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

typedef std::string (*RequestUserInputFromHost) ();
typedef bool (*RequestDataFromDatabaseWithTimeout) (const std::string &query, std::map<std::string, std::vector<std::string>> &dataBaseTable, unsigned int maximumSecondsToWait);
typedef void (*LogDataFromDll)(LogLevel logLevel, std::string& logEntry);
typedef void (*SendProcessedDataToHost) (const std::vector<ProcessedData>& listOfProcessedDataItems);

struct SharedMemory
{
  std::string inputFromDll;
  std::string inputFromHost;
  std::vector<std::string> stringsSharedByDllAndHost;
  CallBackFunctionFromHostToDllPtr callBackFunctionFromHostToDll {nullptr};
  RequestUserInputFromHost  requestUserInputFromHost {nullptr};
  RequestDataFromDatabaseWithTimeout requestDataFromDatabaseWithTimeout {nullptr};
  LogDataFromDll logDataFromDll {nullptr};
  SendProcessedDataToHost sendProcessedDataToHost {nullptr};
};
#endif //DLL_TEST_SHARED_MEMORY_H
