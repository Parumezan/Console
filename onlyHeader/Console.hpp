#include <chrono>
#include <dlfcn.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

enum LogType {
    INFO,
    WARN,
    ERROR
};

class Console
{
    private:
        ssize_t _info;
        ssize_t _warn;
        ssize_t _error;

    public:
        Console()
        {
            this->_info = 0;
            this->_warn = 0;
            this->_error = 0;

            std::cout << "YYYY-MM-DD HH:mm:ss:ms\tfile:function:line\ttype:message" << std::endl;
        }

        ~Console()
        {
            std::cout << "Console: " << this->_info << " info, " << this->_warn << " warn, " << this->_error << " error" << std::endl;
        }

        void log(LogType type, std::string dateAndTime, std::string context, std::string msg)
        {
            std::string generalContext = dateAndTime + "\t" + context + "\t";

#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            switch (type) {
            case INFO:
                this->_info++;
                SetConsoleTextAttribute(hConsole, 15);
                std::cout << generalContext << "INFO:" << msg << std::endl;
                break;
            case WARN:
                this->_warn++;
                SetConsoleTextAttribute(hConsole, 14);
                std::cout << generalContext << "WARN:" << msg << std::endl;
                break;
            case ERROR:
                this->_error++;
                SetConsoleTextAttribute(hConsole, 12);
                std::cerr << generalContext << "ERROR:" << msg << std::endl;
                break;
            }
            SetConsoleTextAttribute(hConsole, 15);
#else
            switch (type) {
            case INFO:
                this->_info++;
                std::cout << "\033[0m" << generalContext << "INFO:" << msg << "\033[0m" << std::endl;
                break;
            case WARN:
                this->_warn++;
                std::cout << "\033[33m" << generalContext << "WARN:" << msg << "\033[0m" << std::endl;
                break;
            case ERROR:
                this->_error++;
                std::cerr << "\033[31m" << generalContext << "ERROR:" << msg << "\033[0m" << std::endl;
                break;
            }
#endif
        }
};

// format date and time as YYYY-MM-DD HH:mm:ss:ms
#define _CONSOLE_ACTUAL_TIME_                                                                                                                                                                                                                                                                              \
    std::string([]() -> std::string {                                                                                                                                                                                                                                                                      \
        auto now = std::chrono::system_clock::now();                                                                                                                                                                                                                                                       \
        auto in_time_t = std::chrono::system_clock::to_time_t(now);                                                                                                                                                                                                                                        \
        std::stringstream ss;                                                                                                                                                                                                                                                                              \
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");                                                                                                                                                                                                                                    \
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());                                                                                                                                \
        return ss.str() + ":" + std::to_string(ms.count());                                                                                                                                                                                                                                                \
    }())

#define _CONSOLE_ACTUAL_CONTEXT_                                                                                                                                                                                                                                                                           \
    std::string([](std::string file, std::string func, std::string line) -> std::string {                                                                                                                                                                                                                  \
        file = file.empty() ? "file?" : file;                                                                                                                                                                                                                                                              \
        func = func.empty() ? "function?" : func;                                                                                                                                                                                                                                                          \
        line = line.empty() ? "line?" : line;                                                                                                                                                                                                                                                              \
        std::string context = file + ":" + func + ":" + line;                                                                                                                                                                                                                                              \
        return context;                                                                                                                                                                                                                                                                                    \
    }(__FILE__, __func__, std::to_string(__LINE__)))

#define LOG(console, type, msg) console->log(type, _CONSOLE_ACTUAL_TIME_, _CONSOLE_ACTUAL_CONTEXT_, msg);
#define LOG_G(type, msg) console->log(type, _CONSOLE_ACTUAL_TIME_, _CONSOLE_ACTUAL_CONTEXT_, msg);