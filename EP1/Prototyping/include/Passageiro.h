/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_
#include <vector>
#include <thread>
#include <algorithm>
#include <sstream>
#include <iostream>
#include "helper.h"
#include <chrono>
#include <utility>
#include <random>

class Carro;
class Parque;

class Passageiro {
	int id;
	Carro *carro;
	Parque *parque;
	std::vector<int>* turns;
	std::thread t;
public:
	Passageiro(Carro *c, int id);
	virtual ~Passageiro();
	void entraNoCarro();
	void join();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	void run();
};

#endif /* PASSAGEIRO_H_ */
