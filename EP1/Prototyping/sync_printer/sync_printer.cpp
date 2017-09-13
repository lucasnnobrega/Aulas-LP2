#include "./sync_printer.h"

std::stringstream sync_cout_t::stringSoFar;
sync_cout_t* sync_cout_t::thisPtr = nullptr;
std::mutex sync_cout_t::mut;
Endl Endl::endl;

Endl* Endl::getEndl(){
	return &endl;
}

sync_cout_t::sync_cout_t(){

}

sync_cout_t& sync_cout_t::getInstance(){
	sync_cout_t::mut.lock();
	if(sync_cout_t::thisPtr == nullptr)
		sync_cout_t::thisPtr = new sync_cout_t;
	return *sync_cout_t::thisPtr;
}

template<>
sync_cout_t& operator<< <Endl*> (sync_cout_t& stream, Endl* value){
	std::cout << sync_cout_t::stringSoFar.rdbuf() << std::endl;
	sync_cout_t::stringSoFar.clear();
	sync_cout_t::mut.unlock();
	return stream;
}

