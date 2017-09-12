/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef __CARRO_H_
#define __CARRO_H_
#include <chrono>
#include <thread>
#include <iostream>
#include <atomic>
#include <utility>
#include "helper.h"

#define DURACAO_DA_VOLTA 2000
#define NUMERO_DE_VOLTAS 20

class Done{};
class Parque;
class Carro{
private:
	std::atomic<int> numPassageiros{0};//Numero de passageiros dentro do carro
	int capacidade; //Numero maximo de passageiros no carro

	int voltas = 0; //Numero de voltas até o parque fechar

	Parque* parque; //Ponteiro para a montanha-russa que contem o carro
	int* turns;
	
	std::thread* thr = nullptr;
public:
	volatile bool voltaAcabou = true; //Está dando uma volta?
	volatile bool cheio = false;
	Carro(int capacidade_, Parque* parque, int* turns);
	Carro(){}
	~Carro();
	void esperaEncher(); //Espere ate que numPassageiros == capacidade
	void daUmaVolta(); //Durma por DURACAO_DA_VOLTA millisegundos
	void esperaEsvaziar(); //Espere ate que numPassageiros == 0

	inline volatile bool getVoltaAcabou(){
		return voltaAcabou;
	}
	inline void incPassageiros(){
		numPassageiros.fetch_add(1);
	}
	inline void decPassageiros(){
		numPassageiros.fetch_add(-1);
	}
	////////Getters////////
	int getNVoltas();
	std::atomic<int>* getNumPassageiros();
	int getCapacidade();
	Parque* getParquePtr();
	std::thread*& getThreadPtr();
	int* getTurnsPtr();
	///////////////////////
	void run();
	void operator()()
	{
		run();
	}
};

#endif /* CARRO_H_ */
