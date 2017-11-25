#include "./include/sync_printer.h"

std::stringstream sync_cout_t::stringSoFar;
sync_cout_t* sync_cout_t::thisPtr = nullptr;
ordered_mutex sync_cout_t::mut;
Endl Endl::endl;

Endl* Endl::getEndl(){
	return &endl;
}

sync_cout_t::sync_cout_t(){

}

sync_cout_t& sync_cout_t::getInstance(){
	//Até que sync_endl seja passado, continue a coletar valores no buffer stringSoFar sem desbloquear o mutex
	sync_cout_t::mut.lock();
	if(sync_cout_t::thisPtr == nullptr) //Protoloco para instanciacao de singleton
		sync_cout_t::thisPtr = new sync_cout_t;
	return *sync_cout_t::thisPtr;
}

template<>
sync_cout_t& operator<< <Endl*> (sync_cout_t& stream, Endl* value){
	//Quando sync_endl for passado como argumento, descarregue o buffer no STDOUT, limpe-o e desloqueie o semaforo 
	std::cout << sync_cout_t::stringSoFar.rdbuf() << std::endl;
	sync_cout_t::stringSoFar.clear();
	sync_cout_t::mut.unlock();
	return stream;
}

