
/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "stdio.h"
#include <cassert>
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 50

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1000,3000);

Passageiro::Passageiro(Carro *c, int id_) {
	id = id_;
	carro = c;
	parque = c->getParquePtr();
	turns = carro->getParquePtr()->getTurnsPtr();
}

Passageiro::~Passageiro() {
	if(t.joinable()){
		t.join();
	}
}

void Passageiro::join(){
	if(t.joinable()){
		t.join();
	}
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	turns->at(id) = 1;
	turns->at(id) = *std::max_element(turns->begin(), turns->end()) + 1 ;
	for(int j = 0; j < turns->size(); j++){
		if(j == id) 
			continue;
		while(!carro->cheio || (turns->at(j) != 0 && (turns->at(id) > turns->at(j) || (turns->at(id) == turns->at(j) && id > j) )) || carro->aberto){
		}
	}
	//CriticalSection
	if(carro->numPassageiros <= carro->capacidade ){
		carro->numPassageiros.fetch_add(1);	
		if(carro->numPassageiros == carro->capacidade){//Se esse passageiro e o ultimo
			carro->aberto = false;
			carro->cheio = true;
		}
	}
	turns->at(id) = 0;

	//NonCriticalSection
	//Log
	std::stringstream stream;
	stream << "O passageiro " << id << " entrou no carro\n";
	std::cout << stream.rdbuf();
	std::cout.flush();
	
}

void Passageiro::esperaVoltaAcabar() {
	while (!carro->aberto) {
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}
}

void Passageiro::saiDoCarro() {
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
	carro->numPassageiros.fetch_add(-1);

//	lock(carro->parque->sharedLock);
	if(carro->numPassageiros == 0){
		carro->cheio = false;
		carro->aberto = true;
	}
//	unlock(carro->parque->sharedLock);

	std::stringstream stream;
	stream << "O passageiro " << id << " saiu do carro\n";
	std::cout << stream.rdbuf();
	std::cout.flush();
}

void Passageiro::passeiaPeloParque() {
	// Dorme um tempo aleatorio
	std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
}

void Passageiro::run() {
	t = std::move(std::thread([this](){
		while (1) {
			entraNoCarro(); 
			esperaVoltaAcabar();
			saiDoCarro(); 
			passeiaPeloParque(); 
		}
	}));

	// decrementa o numero de pessoas no parque
}

