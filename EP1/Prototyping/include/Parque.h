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
	std::vector<Passageiro*> passageiros;//Vetor com todos os passageiros que estão atualmente no parque
	std::vector<int> turns;//Array de turnos compartilhados para algoritmo da padaria
	Carro carro;//Carro da montanha russa
	int numPessoas = 0;//Numero de pessoas ate agora
	public:
	bool parqueFechado;//O parque esta fechado?

	Parque(int capacidade, int maxVoltas);//Construtor
	~Parque();//Destrutor
	
	std::vector<int>* getTurnsPtr();//Retorna endereço do vetor de inteiros compartilhados pelos passageiros
	int getNumPessoas();//Retorna numero de pessoas atualmente no parque
	void addPassageiro(int id);//Dado um id inteiro, construi um passageiro e adiciona-o ao parque

};

#endif /* PARQUE_H_ */
