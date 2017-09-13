/*
 * Parque.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PARQUE_H_
#define PARQUE_H_

#include <vector>
#include <array>
#include "./Carro.h"
#include "./Parque.h"

class Passageiro;


class Parque {
	std::vector<Passageiro*> passageiros;
	std::vector<int> turns;	
	Carro carro;
	int numPessoas = 0;
	public:
	std::atomic_flag sharedLock = ATOMIC_FLAG_INIT;

	Parque(int capacidade, int maxVoltas);
	~Parque();
	
	std::vector<int>* getTurnsPtr();
	int getNumPessoas();
	void addPassageiro(Passageiro *p);
	void addPassageiro(int id);

};

#endif /* PARQUE_H_ */
