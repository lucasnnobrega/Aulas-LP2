//
// Created by luciano on 16/10/17.
//

#include "../include/Pessoa.h"

void Pessoa::dormir() {
	std::this_thread::sleep_for(std::chrono::milliseconds(randomDis()));
}

void Pessoa::entrarNoBanheiro(Banheiro &banheiro){

}

void Pessoa::sairDoBanheiro(){

}

void Pessoa::run(){
	while(1){
		entrarNoBanheiro(banheiroAtual);
	}
}
Pessoa::Pessoa(int n){
	id = n;
	thread 
}