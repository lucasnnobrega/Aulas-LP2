#include "./include/helper.h"

#include <iostream>

std::string Helpers::Printer::stringSoFar = std::string("");
std::mutex Helpers::Printer::mut;

//Entrada em seção crítica com test_and_set
void lock(std::atomic_flag& sharedFlag){
	//CSEnter
	while(sharedFlag.test_and_set()){
		//Garante que loop não seja tomado como redundante e eliminado
		//pelo otimizador durante a compilação com flag -O3
		asm("");
	}
}

void unlock(std::atomic_flag& sharedFlag){
	//CSExit
	sharedFlag.clear();
}

//Bloqueia o mutex no inicio da construçao da string para impressão
void Helpers::Printer::start(){
	Helpers::Printer::mut.lock();
}

//Monta a string para impressão parte a parte, sem desbloquear o mutex
void Helpers::Printer::append(std::string s){
	Helpers::Printer::stringSoFar += s;
}

//Descarrega o buffer stringSoFar em STDOUT, limpa-o e desbloqueia o mutex
void Helpers::Printer::end(){
	std::cout << Helpers::Printer::stringSoFar << std::endl;
	Helpers::Printer::stringSoFar.clear();
	Helpers::Printer::mut.unlock();
}

