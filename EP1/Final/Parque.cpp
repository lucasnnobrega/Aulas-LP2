/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Parque.h"
#include "include/Passageiro.h"
#include <iostream>

Parque::Parque(int capacidadeCarro) : carro(capacidadeCarro, this, turns){

}

Parque::~Parque() {
	for(Passageiro* e : clientes){
		if(e != nullptr){
			if(e->getThreadPtr() != nullptr){
				if(e->getThreadPtr()->joinable())
					e->getThreadPtr()->join();
				delete e;	
			}	
		}
	}
}

int Parque::getNumeroDeClientes(){
	return numeroDeClientes;
}

int* Parque::getTurnsPtr(){
	return &turns[0];
}

void Parque::addCliente(int id){
	//Adicione o passageiro a lista de clientes no parque
	Passageiro* passageiro = new Passageiro(id, &carro);
	clientes[numeroDeClientes++] = passageiro; 
}

void Parque::runClientes(){
	for(int i = 0; i < numeroDeClientes; i++)
		clientes[i]->run();
}

void Parque::runCarro(){
	carro.run();
}

