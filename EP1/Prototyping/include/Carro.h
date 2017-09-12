/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_
#include <atomic>
#include <thread>
#include "helper.h"
#include <utility>
#include <vector>

#define DURACAO_DA_VOLTA 8000

class Parque;

class Carro {
	std::atomic<int> numPassageiros{0};
	int numPassageirosAux = 0;
	bool aberto;
	bool cheio;
	bool vazio = true;
	int voltas;
	int capacidade;
	Parque *parque;
	std::thread t;
	std::vector<int>* turns;

	public:

	Carro(Parque *p, int capacidade);
	~Carro();
	void join();

	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();

	int getNVoltas();
	Parque* getParquePtr();

	void run();

	void operator()()
	{
		run();
	}

	friend class Passageiro;
};

#endif /* CARRO_H_ */
