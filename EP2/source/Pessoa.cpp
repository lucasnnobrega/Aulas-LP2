//
// Created by luciano on 16/10/17.
//

#include "../include/Pessoa.h"

bool Pessoa::barreira = false;

void Pessoa::dormir() {
	int duration = randomDis();
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void Pessoa::entrarNoBanheiro(Banheiro* banheiro){

}

void Pessoa::sairDoBanheiro(){

}

int Pessoa::getId(){
	return id;
}

void Pessoa::run(){
	while(1){
		entrarNoBanheiro(banheiroAtual);
		dormir();
		sairDoBanheiro();
		dormir();
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
