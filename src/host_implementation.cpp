//
// Created by xnorxnor on 27.05.2019.
//

#include "shared_memory.h"
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <sstream>

/*
typedef std::string (*RequestUserInputFromHost) ();
typedef bool (*RequestDataFromDatabaseWithTimeout) (const std::string &query, std::map<std::string, std::vector<std::string>> &dataBaseTable, unsigned int maximumSecondsToWait);
typedef void (*LogDataFromDll)(LogLevel logLevel, std::string& logEntry);
typedef void (*SendProcessedDataToHost) (const std::vector<ProcessedData>& listOfProcessedDataItems);
*/

std::string GenerateUserInputData()
{
  std::string userInput;

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);

  std::ostringstream oss;
  oss << "user input [" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "]";
  userInput = oss.str();

  return userInput;
}

std::string RequestUserInputFromHost()
{
  // normally, a user dialog would show up here
  // we generate some fake user input data here
  return GenerateUserInputData();
}