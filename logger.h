#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <cstring>
#include <fstream>
#include "object.h"

#define POS __FILE__, __LINE__, __FUNCTION__ //position in code

enum class LogOutput
{
	Console = 1,
	TxtFile = 2,
	TxtFileAndConsole = 3 
};

enum class LogType
{
	Information = 1, 
	Success = 2,
	Error = 3,
	Fatal = 4
};

class Logger : public ezo::Object
{
public:

	//Writes message on output if msgtype is equal/higher than minPriority
	void log(const char* message, LogType msgtype = LogType::Information,	LogOutput output = LogOutput::TxtFile);


	//Specialized log method, shows informations about position in code
	void log(const char* file, int line, const char* function, const std::string& message,
			LogType msgtype = LogType::Information, LogOutput output = LogOutput::TxtFile);

	//Writes all from buffer to file and clears buffer
	void saveLogs();

	//Sets priority, only logs with equal/higher priority will be write
	void setPriority(LogType priority) { minPriority = priority; }

	void setBufferSize(unsigned int size) { buffSize = size; }

	//activate/disable logger
    void activate() { active = true; }
    void disable() { active = false; }

    Logger(const char* filename = "logz/log_default");
	~Logger();
	
	//temp
	std::string fstr(const std::string fmt, ...);
	
private:
	//Only logs with priority equal or higher than this value will be writed
	LogType minPriority; 

	//Buffer for logs to file
	std::vector<std::string> txtBuffer;

	char filename[128]; //24 for time/date

	//for time tag
	time_t currentTime;

	//for filename
	tm* currentDate;

	//logfile handle
	FILE* logFile;

	//Logger work only if active is true. Logger is active by default.
	bool active;

	unsigned int buffSize; //bigger - faster but if app crash some logs will not be saved  
};
