#include "../include/Log.h"

time_t Log::s_currentTime;
Log Log::s_Instance;
Log::LogLevel Log::s_currentLogLevel = LogLevelTrace;

#if defined(_WIN32)
    HANDLE Log::s_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif 

std::ofstream Log::s_fp("Log.txt", std::ios_base::app);

Log& Log::Get() 
{
    return s_Instance; 
}

void Log::SetLevel(LogLevel newLevel)
{
    s_currentLogLevel = newLevel;
    if (newLevel == LogLevelTrace)
        s_fp << "[LEVEL CHANGED TO]: LogLevelTrace" << std::endl << std::endl;
    if (newLevel == LogLevelWarn) 
        s_fp << "[LEVEL CHANGED TO]: LogLevelWarn" << std::endl << std::endl;
    else 
        s_fp << "[LEVEL CHANGED TO]: LogLevelError" << std::endl << std::endl;
}

#if defined(_WIN32)
    void Log::SetDefaultColor()
    {
        SetConsoleTextAttribute(s_hConsole, COLOR_DEFAULT_WINDOWS);
    }
    
#elif defined(__unix__)
    void Log::SetDefaultColor()
    {
        COLOR_DEFAULT_LINUX
    }
#endif

#if defined(_WIN32)
void Log::Trace(bool dateStamped, bool printToConsole, bool printToFile, const char *message)
{
    if (s_currentLogLevel <= LogLevelWarn)
    {
        std::time(&s_currentTime);       
        
        if (printToFile)
        {
            if (dateStamped)
                s_fp << std::ctime(&s_currentTime) << "[TRACE]: " << message << std::endl << std::endl;
            else
                s_fp << "[TRACE]: " << message << std::endl << std::endl;
        }
        if (printToConsole)
        {
            SetConsoleTextAttribute(s_hConsole, COLOR_GREEN_WINDOWS);
            if (dateStamped)
                std::cout << std::ctime(&s_currentTime) << "[TRACE]: " << message << std::endl;
            else 
                std::cout << "[TRACE]: " << message << std::endl;
        }
    }
    SetDefaultColor();
}

void Log::Warn(bool dateStamped, bool printToConsole, bool printToFile, const char* message)
{
    if (s_currentLogLevel <= LogLevelWarn)
    {
        std::time(&s_currentTime);

        if (printToFile)
        {
            if (dateStamped)
                s_fp << std::ctime(&s_currentTime) << "[WARNING]: " << message << std::endl << std::endl;
            else
                s_fp << "[WARNING]: " << message << std::endl << std::endl;
        }
        if (printToConsole)
        {
            SetConsoleTextAttribute(s_hConsole, COLOR_PURPLE_WINDOWS);
            
            if (dateStamped)
                std::cout << std::ctime(&s_currentTime) << "[WARNING]: " << message << std::endl;
            else
                std::cout << "[WARNING]: " << message << std::endl;
        }
    }
    SetDefaultColor();
}

void Log::Error(bool dateStamped, bool printToConsole, bool printToFile, const char* message)
{
    if (s_currentLogLevel <= LogLevelError)
    {
        std::time(&s_currentTime);

        if (printToFile)
        {
            if (dateStamped)
                s_fp << std::ctime(&s_currentTime) << "[ERROR]: " << message << std::endl << std::endl;
            else
                s_fp << "[ERROR]: " << message << std::endl << std::endl;
        }
        if (printToConsole)
        {
            SetConsoleTextAttribute(s_hConsole, COLOR_RED_WINDOWS);
            if (dateStamped)
                std::cout << std::ctime(&s_currentTime) << "[ERROR]: " << message << std::endl;
            else
                std::cout << "[ERROR]: " << message << std::endl;
        }
    }
    SetDefaultColor();
}

#elif defined(__unix__)
    void Log::Trace(bool dateStamped, bool printToConsole, bool printToFile, const char* message)
    {
        if (s_currentLogLevel <= LogLevelWarn)
        {
            std::time(&s_currentTime);

            if (printToFile)
            {
                if (dateStamped)
                    s_fp << std::ctime(&s_currentTime) << "[TRACE]: " << message << std::endl << std::endl;
                else
                    s_fp << "[TRACE]: " << message << std::endl << std::endl;
            }
            if (printToConsole)
            {
                COLOR_GREEN_LINUX
                if (dateStamped)
                    std::cout << std::ctime(&s_currentTime) << "[TRACE]: " << message << std::endl;
                else
                    std::cout << "[TRACE]: " << message << std::endl;
            }
        }
        SetDefaultColor();
    }

    void Log::Warn(bool dateStamped, bool printToConsole, bool printToFile, const char* message)
    {
        if (s_currentLogLevel <= LogLevelWarn)
        {
            std::time(&s_currentTime);

            if (printToFile)
            {
                if (dateStamped)
                    s_fp << std::ctime(&s_currentTime) << "[WARNING]: " << message << std::endl << std::endl;
                else
                    s_fp << "[WARNING]: " << message << std::endl << std::endl;
            }
            if (printToConsole)
            {
                COLOR_PURPLE_LINUX
                if (dateStamped)
                    std::cout << std::ctime(&s_currentTime) << "[WARNING]: " << message << std::endl;
                else
                    std::cout << "[WARNING]: " << message << std::endl;
            }
        }
        SetDefaultColor();
    }

    void Log::Error(bool dateStamped, bool printToConsole, bool printToFile, const char* message)
    {
        if (s_currentLogLevel <= LogLevelError)
        {
            std::time(&s_currentTime);

            if (printToFile)
            {
                if (dateStamped)
                    s_fp << std::ctime(&s_currentTime) << "[ERROR]: " << message << std::endl << std::endl;
                else
                    s_fp << "[ERROR]: " << message << std::endl << std::endl;
            }
            if (printToConsole)
            {
                COLOR_RED_LINUX
                if (dateStamped)
                    std::cout << std::ctime(&s_currentTime) << "[ERROR]: " << message << std::endl;
                else
                    std::cout << "[ERROR]: " << message << std::endl;
        }
        }
        SetDefaultColor();
    }

#endif

void Log::SpecifyLogFile(const char *filePath)
{
    if (filePath == nullptr)
        s_fp.open("Log.txt", std::ios_base::app);
    else 
        s_fp.open(filePath, std::ios_base::app);
}