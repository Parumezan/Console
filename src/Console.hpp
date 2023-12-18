#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

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
        std::string _dateAndTime();

    public:
        Console();
        ~Console();
        void log(LogType type, std::string context, std::string msg);
};

#define _CONSOLE_ACTUAL_CONTEXT_                                                                                                                                                                                                                                                                           \
    std::string([](std::string file, std::string func, std::string line) -> std::string {                                                                                                                                                                                                                  \
        file = file.empty() ? "file?" : file;                                                                                                                                                                                                                                                              \
        func = func.empty() ? "function?" : func;                                                                                                                                                                                                                                                          \
        line = line.empty() ? "line?" : line;                                                                                                                                                                                                                                                              \
        std::string context = file + ":" + func + ":" + line;                                                                                                                                                                                                                                              \
        return context;                                                                                                                                                                                                                                                                                    \
    }(__FILE__, __func__, std::to_string(__LINE__)))

#define LOG(console, type, msg) console->log(type, _CONSOLE_ACTUAL_CONTEXT_, msg);
#define LOG_G(type, msg) console->log(type, _CONSOLE_ACTUAL_CONTEXT_, msg);

#endif /* !CONSOLE_HPP_ */