
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>


class Printer
{   
private:
    static std::mutex m;
public:
    void exec()
    {
        //std::mutex m;
        Printer.m.lock();
        std::cout << "Hello  "<< std::this_thread::get_id() <<std::endl;
        std::chrono::milliseconds duration( 100 );
        std::this_thread::sleep_for( duration );
        Printer.m.unlock();

    }
};

int main()
{
    Printer printer;

    std::thread firstThread([&printer](){
        while(1)
            printer.exec();

    });
    std::thread secondThread([&printer](){
        while(1)
            printer.exec();
    });

    firstThread.join();
    secondThread.join();     
}