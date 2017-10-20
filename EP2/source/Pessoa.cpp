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

