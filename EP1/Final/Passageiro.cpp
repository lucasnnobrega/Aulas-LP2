/* 
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 50

Passageiro::Passageiro(int id_, Carro* c) : id(id_), carro(c), randomSleep(MIN_PASSEIO, MAX_PASSEIO){
	generator.seed(rd());
	turns = c->getTurnsPtr();
}


bool Passageiro::getPasseando(){
	return passeando;
}

std::thread* Passageiro::getThreadPtr(){
	return thr;
}

Passageiro::~Passageiro() {
	if(thr != nullptr){
		if(thr->joinable()){
			thr->join();
		}
		delete thr;
	}
}

void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	turns[id] = 1;
	turns[id] = std::max(turns[0], turns[carro->getParquePtr()->getNumeroDeClientes() - 1]) + 1;
	for(int j = 0; j < carro->getParquePtr()->getNumeroDeClientes() && j != id; j++){
		while(carro->cheio || turns[j] != 0 && (turns[id] > turns[j] || (turns[id] == turns[j] && id > j))){
		}
	}
	// Incrementa o numero de passageiros no carro (use a funcao fetch_add)
	if(carro->getNumPassageiros()->load() <= carro->getCapacidade()){
		carro->voltaAcabou = false;
		carro->incPassageiros();
		//Log
		std::stringstream stream;
		stream << "Passageiro: " << id << " entrou\n";
		std::cout << stream.rdbuf();
	}
	else{
		carro->cheio = true;
	}
	turns[id] = 0;
}

void Passageiro::esperaVoltaAcabar(){
	//Lock para leitura
	while(!carro->getVoltaAcabou()){
//		lock(carro->getParquePtr()->parqueSharedLock);//CSEnter
//		if(carro->getVoltaAcabou()) 
//			break;
//		unlock(carro->getParquePtr()->parqueSharedLock);//CSExit	
	}
}


void Passageiro::saiDoCarro() {
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
//	if(carro->cheio) carro->cheio = false;
	carro->decPassageiros();	
	//Log
	std::stringstream stream;
	stream << "Passageiro: " << id << " saiu\n";
	std::cout << stream.rdbuf();
}

void Passageiro::passeiaPeloParque() {
	passeando = true;
	std::this_thread::sleep_for(std::chrono::milliseconds(randomSleep(generator)));	
	passeando = false;
}

void Passageiro::run() {
	thr = new std::thread([&](){
		while (1) {
			entraNoCarro(); // protocolo de entrada
	
			esperaVoltaAcabar();
	
			saiDoCarro(); // protocolo de saida
	
			passeiaPeloParque(); // secao nao critica
		}
	});
}

