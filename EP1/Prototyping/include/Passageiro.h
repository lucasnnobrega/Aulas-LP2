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
#include "./Passageiro.h"

class Carro;
class Parque;

class Passageiro {
	int id; //Id do passageiro atual
	Carro *carro;//Endereço do carro que esse passageiro tentara entrar
	Parque *parque;//Endereço do parque que contem o carro acima
	std::vector<int>* turns;//Endereço do array de inteiros compartilhados
	std::thread t;//Thread com loop de ação desse passageiro
public:
	static int minSleep;
	static int maxSleep;

	Passageiro(Carro *c, int id);//Construtor
	virtual ~Passageiro();//Destrutor
	void entraNoCarro();//Entrada no carro, protegida pelo algoritmo da padaria;
	void join();//se t.joinable(), t.join()
	void esperaVoltaAcabar();//Espera ocupada
	std::thread* getThreadPtr();//Retorna endereço da thread desse passageiro
	void saiDoCarro();//Espera ocupada
	void passeiaPeloParque();//Dorme um tempo aleatorio

	void run();//Inicia t com start
	void start();//Loop de ação desse passageiro
};

#endif /* PASSAGEIRO_H_ */
