#include "./include/helper.h"

#include <iostream>


void lock(std::atomic_flag& sharedFlag){
	while(sharedFlag.test_and_set()){
		asm("");
	}
}

void unlock(std::atomic_flag& sharedFlag){
	sharedFlag.clear();
}
