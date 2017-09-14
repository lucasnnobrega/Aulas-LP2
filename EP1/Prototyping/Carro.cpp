/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "include/Parque.h"
#include "include/helper.h"
#include <iostream>
//namespace para escever de maneira simplificada no sleep
using namespace std::chrono_literals;
//namespace de helpers no printer
using namespace Helpers;

//Construtor de carro
Carro::Carro(Parque *p, int capacidade_, int maxVoltas_) {
	capacidade = capacidade_;
	turns = p->getTurnsPtr();
	parque = p;
	cheio = false;
	voltaAcabou = false;
	voltas = 0;
	maxVoltas = maxVoltas_;
	saindo = false;
}

Carro::~Carro() {
	join();
}

void Carro::join(){
	if(t.joinable())
		t.join();
}


bool Carro::joinable(){
	return (t.joinable()) ? true:false;
}

//Esperando encher o carro, aguardando algoritmo da padaria
void Carro::esperaEncher() {
	//LOG
	Printer::start();
	Printer::append("Esperando encher");
	Printer::end();
	
	//Para que os proximos não passem direto
	voltaAcabou = false;
	saindo = false;
	//Aguardando encher, dormindo
	while (!cheio){
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	//LOG
	Printer::start();
	Printer::append("Cheio");
	Printer::end();

}

void Carro::daUmaVolta() {
	//Dorme por um tempo fixo
	voltaAcabou = false;
	std::this_thread::sleep_for(std::chrono::milliseconds(DURACAO_DA_VOLTA));
	voltaAcabou = true;
	//LOG
	Printer::start();
	Printer::append("Iniciando uma volta");
	Printer::end();
}

//Esperando o fetch_add(-1)
void Carro::esperaEsvaziar() {
	saindo = true;
	//LOG
	Printer::start();
	Printer::append("Esperando esvaziar");
	Printer::end();

	//Aguarda enquanto nao sairam todos
	while( cheio  ){
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	
	//LOG
	Printer::start();
	Printer::append("Carro vazio");
	Printer::end();
}

//Metodo não utilizado
int Carro::getNVoltas() {
	return voltas;
}

//Passageiro, pegando ponteiro de parque a partir de carro
Parque* Carro::getParquePtr(){
	return parque;
}

//Loop de execução do carro
void Carro::start(){
	while (parque->getNumPessoas() >= 0 && voltas <= maxVoltas) {
		esperaEncher();
		daUmaVolta();
		esperaEsvaziar();
		voltas++;
		//Quando acabarem as voltas
		if(voltas == maxVoltas){
			parque->parqueFechado = true;
			//LOG
			Printer::start();
			Printer::append("O parque fechou");
			Printer::end();
			std::exit(1);
			break;
		}
	}
}
//Execução do carro
void Carro::run() {
	//está sendo atribuido a t o endereço da thread passageiro
	//execuçãod o metodo start
	t = std::thread(&Carro::start, this);	
}
