//Printer.h
#ifndef PRINTER_H
#define PRINTER_H
#include <iostream>
#include <mutex>
#include <chrono>

class Printer
{

    private:
        static std::mutex mut;

    public:
 //       std::ostream& operator<<(std::ostream& stream, std::string& s);
        void exec();
        
};


#endif //Printer.h