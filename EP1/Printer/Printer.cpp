#include "./include/Printer.h"

using namespace std;

mutex Printer::mut;
/*
std::ostream& Printer::operator<< (std::ostream& stream, std::string& s){
    mut.lock();
    stream << s;
    mut.unlock();
    return stream;

}
*/
void Printer::exec()
{
    mutex m;
    m.lock();
    cout<<"Hello  "<<this_thread::get_id()<<endl;
    chrono::milliseconds duration( 100 );
    this_thread::sleep_for( 10 );
    m.unlock();

}