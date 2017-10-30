//
// Created by luciano on 16/10/17.
//

#include "../include/Pessoa.h"

bool Pessoa::barreira = false;

void Pessoa::dormir() {
	int duration = randomDis();
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

int Pessoa::entrarNoBanheiro(Banheiro* banheiro){

}

void Pessoa::sairDoBanheiro(){

}

int Pessoa::getId(){
	return id;
}

void Pessoa::run(){
	Logger::log(CHEGOU_NO_ESTABELECIMENTO, id);
	while(1){
		if(banheiroAtual->nUtilizacoes + 1 <= banheiroAtual->maxUtilizacao)
		{	
			entrarNoBanheiro(banheiroAtual);	
			//Caso o banheiro tenha fechado enquanto estava na fila, va embora
			dormir();
			sairDoBanheiro();
			dormir();
		}else{
			break;
		}
	}
}

Pessoa::~Pessoa(){
	if(thread->joinable()){
		thread->join();
	}
}

Pessoa::Pessoa(int n){
	id = n;
	thread = new std::thread(&Pessoa::run, this);				
}
