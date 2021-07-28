#pragma once

// Log Macros
#define LOG_TRACE(dateStamped, printToConsole, printToFile, message) Log::Get().Trace(dateStamped, printToConsole, printToFile, message); 
#define LOG_WARN(dateStamped, printToConsole, printToFile, message) Log::Get().Warn(dateStamped, printToConsole, printToFile, message);
#define LOG_ERROR(dateStamped, printToConsole, printToFile, message) Log::Get().Error(dateStamped, printToConsole, printToFile, message);
#define LOG_SETLEVEL(newLevel) Log::Get().SetLevel(Log::newLevel);
#define LOG_SETDEFAULTCOLOR Log::Get().SetDefaultColor();
#define LOG_SPECIFYLOGFILE(filePath) Log::Get().SpecifyLogFile(filePath);

#if defined(_WIN32)
    // #defines for function SetConsoleTextAttribute() found in windows.h
    // #define COLOR_GRAY_WINDOWS  8 
    #define COLOR_RED_WINDOWS   4
    #define COLOR_GREEN_WINDOWS 10
    #define COLOR_PURPLE_WINDOWS 13
    #define COLOR_DEFAULT_WINDOWS 7
#endif

#if defined(__unix__)
    // Macros to easily change console color in linux
    #define COLOR_RED_LINUX printf("\033[1;31m");
    #define COLOR_GREEN_LINUX printf("\033[0;32m");
    #define COLOR_PURPLE_LINUX printf("\033[0;35m");
    #define COLOR_DEFAULT_LINUX printf("\033[0m");
#endif

#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(__unix__)
#include <unistd.h>
#endif

#include <iostream>
#include <ctime>
#include <fstream>

class Log
{
public:
    enum LogLevel 
    {
        LogLevelTrace = 0, LogLevelWarn = 1, LogLevelError = 2
    };
private:
    static void SetDefaultColor();
public:
    static void SetLevel(LogLevel newLevel);
    static Log& Get();
    static void Trace(bool dateStamped, bool printToConsole, bool printToFile, const char *message);
    static void Warn(bool dateStamped, bool  printToConsole, bool printToFile, const char *message);
    static void Error(bool dateStamped, bool printToConsole, bool printToFile, const char *message);
    static void SpecifyLogFile(const char *filePath);
private:
    static time_t s_currentTime;

#if defined(_WIN32)
    static HANDLE s_hConsole;
#endif
    
    static Log s_Instance;
    static LogLevel s_currentLogLevel;
    static std::ofstream s_fp;
};