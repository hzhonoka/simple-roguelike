#include <iostream>
#include <fstream>
#include "CreateLog.h"
#include<windows.h>
void Log()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    std::ofstream out("log.txt", std::ios::app);
    if (!out.is_open()) {
        std::cout << "fail to open file log.txt" << std::endl;
    }
    out << "running in " << __DATE__ << " " << __TIME__ << " running successfully" << std::endl << std::endl;
    out.close();
    std::cout << "log has been written in logs.txt" << std::endl;
    return;
}
