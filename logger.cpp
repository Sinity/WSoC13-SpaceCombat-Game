#include "logger.h"

Logger::Logger(const char* filename) :
    minPriority(LogType::Information),
    active(true), buffSize(00)
{
    currentTime = time(0);
    currentDate = localtime(&currentTime);

    strcpy(this->filename, filename);
    strcat(this->filename, fstr("-%d-%d-%d@%d.%d.%d.txt",
            currentDate->tm_hour, currentDate->tm_min, currentDate->tm_sec,
            currentDate->tm_mday, currentDate->tm_mon+1,
            currentDate->tm_year+1900).c_str());

    logFile = fopen(this->filename, "w");
    if(!logFile)
        printf("Cannot open file: %s. Probably folders does'nt exist, so create it if you want see logs\n", this->filename);

    log(POS, "Logger initialized.");

    buffSize = 0;
}


Logger::~Logger(void)
{
    saveLogs();
    fclose(logFile);
}

void Logger::saveLogs()
{
    if(logFile == nullptr)
        return;

    for(unsigned int i = 0; i < txtBuffer.size(); i++)
        fprintf(logFile, "%s\n", txtBuffer[i].c_str());

    fflush(logFile);
    txtBuffer.clear();
}

void Logger::log(const char* message, LogType msgtype, LogOutput output)
{
    //is logger activated?
    if(!active)
        return;

    //check priority
    if((int)msgtype < (int)minPriority)
        return;

    /******PREPARE MESSAGE******/

    //Get current time
    currentTime = time(0);
    currentDate = localtime(&currentTime);

    //set time tag
    std::string logtxt = fstr("[%d:%d:%d] ",
                                currentDate->tm_hour, currentDate->tm_min,
                                currentDate->tm_sec);

    //set message type tag
    switch(msgtype)
    {
    case LogType::Information:
        logtxt += "[INFO] ";
        break;
    case LogType::Error:
        logtxt += "[ERROR] ";
        break;
    case LogType::Success:
        logtxt += "[SUCCESS] ";
        break;
    case LogType::Fatal:
        logtxt += "[FATAL] ";
        break;
    default:	//ERROR: caller sets wrong msgtype

        //message type for log from caller
        logtxt += "[UNDEFINED MSGTYPE] ";

        //log from this func(because msgtype is wrong)
        log(POS, fstr("wrong msgtype: %d!", (int)msgtype));
        break;
    }

    //add message to log
    logtxt += message;

    /********Write this to destination*******/
    switch(output)
    {
    case LogOutput::TxtFileAndConsole:
        printf("%s\n", logtxt.c_str());

    case LogOutput::TxtFile:
        txtBuffer.push_back(logtxt);
        if(txtBuffer.size() > buffSize)
            saveLogs();
        break;

    case LogOutput::Console:
        printf("%s\n", logtxt.c_str());
        break;

    default: //ERROR: caller sets wrong output type
        log(POS, fstr("wrong output type: %d! Message: %s", (int)output, message));
    }
}

void Logger::log(const char* file, int line, const char* function,
                const std::string& message, LogType msgtype, LogOutput output)
{
    log( fstr("%s[%d]@%s - %s", file, line, function,
                            message.c_str()).c_str(), msgtype, output);
}

//not mine, and only temp
#include <cstdarg>
std::string Logger::fstr(const std::string fmt, ...)
{
    int size = 100;
    std::string str;
    va_list ap;
    while (1) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n + 1;
        else
            size *= 2;
    }
    return str;
}
