/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_ 
#include <random>
#include <sstream>
#include <chrono>
#include <iostream>
#include <atomic>
#include <thread>

#define MIN_PASSEIO 2000
#define MAX_PASSEIO 4000
class Carro;
class Passageiro {
	private:
	std::random_device rd;	
	std::mt19937 generator;
	std::uniform_int_distribution<> randomSleep;

	std::thread* thr; 
	int id; //Id do passageiro para algoritmo da padaria
	bool passeando = false; //Atributo para construção do log de passageiros passeando vs no carro
	Carro *carro;

	int* turns;//Array de turnos para algoritmo da padaria
	public:
	Passageiro(int id, Carro *c);
	Passageiro(const Passageiro&);
	~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool getPasseando();
	bool parqueFechado();
	std::thread* getThreadPtr();

	void run();
};
#endif /* PASSAGEIRO_H_ */
