#include "Console.hpp"

Console::Console()
{
    this->_info = 0;
    this->_warn = 0;
    this->_error = 0;

    std::cout << "YYYY-MM-DD HH:mm:ss:ms\tfile:function:line\ttype:message" << std::endl;
}

Console::~Console()
{
    std::cout << "Console: " << this->_info << " info, " << this->_warn << " warn, " << this->_error << " error" << std::endl;
}

std::string Console::_dateAndTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;

    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

    return ss.str() + ":" + std::to_string(ms.count());
}

void Console::log(LogType type, std::string context, std::string msg)
{
    std::string generalContext = this->_dateAndTime() + "\t" + context + "\t";

#ifdef _WIN32 // ! Futur implementation
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