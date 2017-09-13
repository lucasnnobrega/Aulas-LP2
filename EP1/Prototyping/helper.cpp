#include "./include/helper.h"

#include <iostream>

std::string Helpers::Printer::stringSoFar = std::string("");
std::mutex Helpers::Printer::mut;


void lock(std::atomic_flag& sharedFlag){
	while(sharedFlag.test_and_set()){
		asm("");
	}
}

void unlock(std::atomic_flag& sharedFlag){
	sharedFlag.clear();
}

void Helpers::Printer::start(){
	Helpers::Printer::mut.lock();
}

void Helpers::Printer::append(std::string s){
	Helpers::Printer::stringSoFar += s;
}

void Helpers::Printer::end(){
	std::cout << Helpers::Printer::stringSoFar << std::endl;
	Helpers::Printer::stringSoFar.clear();
	Helpers::Printer::mut.unlock();
}

