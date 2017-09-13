#ifndef __EP1HELPERS__
#define __EP1HELPERS__
#include <atomic>
#include <mutex>
void lock(std::atomic_flag&);
void unlock(std::atomic_flag&);
//------------------------------------
namespace Helpers{
	/*
	int endl = 9;
	template<int n = 1>
	class sync_cout{
		static std::mutex mut;
		std::string stringSoFar = "";
		public:
		sync_cout(){
			mut.lock();
		}
		void appendString(std::string& s);

		template<typename T>
		sync_cout& operator<<(T value);
	};
	template<> 
	void sync_cout<1>::appendString(std::string& s){
		stringSoFar += s;
	}
	template<> template<>
	sync_cout<1>& sync_cout<1>::operator<<<std::string> (std::string& value){
		stream.appendString(std::forward<std::string>(value)) ;
		return *this;
	}
	template<> sync_cout& sync_cout::(operator<<)<int> (int value){
		if(value == Helpers::endl ){
			std::cout << stream.stringSoFar << std::endl;
			mut.unlock();
		}
	}
	*/
}
#endif //__EP1HELPERS__
