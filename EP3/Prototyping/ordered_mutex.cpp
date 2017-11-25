#include "./include/ordered_mutex.h"

void ordered_mutex::lock(){
	std::unique_lock<std::mutex> acquire(cvar_lock);
	if(locked){
		cvar.emplace();
		cvar.back().wait(acquire);
	}else{
		locked = true;
	}
}

void ordered_mutex::unlock(){
	std::unique_lock<std::mutex> acquire(cvar_lock);
	if(cvar.empty()){
		locked = false;
	}else{
		cvar.front().notify_one();
		cvar.pop();
	}
}

