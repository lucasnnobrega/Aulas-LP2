#ifndef __SYNC__PRINTER__HELPER__
#define __SYNC__PRINTER__HELPER__
#include <string>
#include <sstream>
#include <iostream>
#include <type_traits>
#include <mutex>
class Endl{
	static Endl endl;
	Endl(){};
	public:
	static Endl* getEndl();
};
class sync_cout_t{
	static std::stringstream stringSoFar;
	static std::mutex mut;
	static sync_cout_t* thisPtr; 
	sync_cout_t();
	public:
	static sync_cout_t& getInstance();

	template<typename T>
	friend sync_cout_t& operator<< (sync_cout_t& stream, T value);
};			
template<typename T>
sync_cout_t& operator<< (sync_cout_t& stream, T value){
	sync_cout_t::stringSoFar << value;
}
#define sync_cout sync_cout_t::getInstance()
#define sync_endl Endl::getEndl()
#endif//__SYNC_PRINTER__HELPER__

