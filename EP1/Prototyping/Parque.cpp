/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Parque.h"
#include "include/Passageiro.h"


Parque::Parque(int capacidade) : carro(this, capacidade) {
	carro.run();
}

Parque::~Parque() {
	for(Passageiro* p : passageiros){
		p->join();	
	}
	carro.join();
	for(Passageiro* p : passageiros){
		delete p;	
	}

}

int Parque::getNumPessoas(){
	return numPessoas;
}

std::vector<int>* Parque::getTurnsPtr(){
	return &turns;
}

void Parque::addPassageiro(Passageiro *p) {
	turns.push_back(0);
	passageiros.push_back(p);
}

void Parque::addPassageiro(int id){
	Passageiro* newPassageiro = new Passageiro(&carro, id);
	turns.push_back(0);
	newPassageiro->run();
	passageiros.push_back(newPassageiro);
}


