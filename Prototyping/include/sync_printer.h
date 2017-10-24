#ifndef __SYNC__PRINTER__HELPER__
#define __SYNC__PRINTER__HELPER__
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <mutex>
#include "fifo_mutex.h"
//Essa classe, quando passada para o operador<< sobrecarregado, ira garantir que o buffer stringSoFar seja empurrado para std::cout.
class Endl{
	static Endl endl;
	Endl(){};
	public:
	static Endl* getEndl();
};

//Singleton que representa o acesso a STDOUT de forma segura atraves do uso de semaforo (mutex)
class sync_cout_t{
	static std::stringstream stringSoFar;
	static std::mutex mut;
	static sync_cout_t* thisPtr; 
	sync_cout_t(); //Construtor privado, conformando definição de uma singleton
	public:
	static sync_cout_t& getInstance(); 

	template<typename T>
	friend sync_cout_t& operator<< (sync_cout_t& stream, T value);
};			
template<typename T> //Para qualquer tipo diferente de Endl, colete em stringSoFar a string que representa o valor passado como argumento
sync_cout_t& operator<< (sync_cout_t& stream, T value){
	sync_cout_t::stringSoFar << value;
}
//Macros que permitem a utilização do sync_cout de forma semelhante ao std::cout, sem a syntax de chamada de funcao
#define sync_cout sync_cout_t::getInstance()
#define sync_endl Endl::getEndl() 
#endif//__SYNC_PRINTER__HELPER__

