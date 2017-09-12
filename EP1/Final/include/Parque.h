/*
 * Parque.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PARQUE_H_
#define PARQUE_H_
#include <vector>
#include <thread>
#include <atomic>
#include <utility>
#include "./Passageiro.h"
#include "./Carro.h"
#define CAPACIDADE_PARQUE 20

class Parque { //A montanha-russa
	Carro carro; 
	Passageiro* clientes[CAPACIDADE_PARQUE] = {nullptr}; //Pessoas tentendo entrar no brinquedo
	int turns[CAPACIDADE_PARQUE] = {0}; //Turnos compartilhado entre todos os passageiros para Algoritmo da Padaria
	int numeroDeClientes = 0; 
	public:
	std::atomic_flag parqueSharedLock = ATOMIC_FLAG_INIT;
	Parque(int capacidadeCarro);
	~Parque();
	void addCliente(int id); //Adiciona passageiro ao vetor de clientes e atualiza total de clientes
	void runClientes(); //Inicia as threads de cada passageiro
	void runCarro();
	int getNumeroDeClientes(); 
	void log(){};
	int* getTurnsPtr();

};

#endif /* PARQUE_H_ */
