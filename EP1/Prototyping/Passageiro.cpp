
/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "stdio.h"
#include <cassert>
#include "include/Carro.h"
#include "include/Parque.h"

#define MAX_NUM_VOLTAS 50

// Random para distribuir o tempo de passeio
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1000,3000);

// Acesso de printer, sem necessidade de colocar helpers
using namespace Helpers;

//Construtor de Passageiro
Passageiro::Passageiro(Carro *c, int id_) {
	id = id_; // id de passageiro
	carro = c; // definição do ponteiro para carro
	parque = c->getParquePtr(); // ponteiro de carro para o parque
	turns = carro->getParquePtr()->getTurnsPtr(); // inicialização do ponteiro para turn'
}

//Destrutor de passageiro 
Passageiro::~Passageiro() {
	if(t.joinable()){
		t.join();
	}
}
//Retornando o endereço da thread desse passageiros
std::thread* Passageiro::getThreadPtr(){
	return &t;
}

//Protocolo de entrada no carro protegida pelo algoritmo da padaria
void Passageiro::entraNoCarro() {
	// Protocolo de entrada o Algoritmo da Padaria
	turns->at(id) = 1;//Na primeira iteração, cada passageiro recebe ticket 1
	turns->at(id) = *std::max_element(turns->begin(), turns->end()) + 1 ; //Calculando maximo
	for(int j = 0; j < turns->size(); j++){//conferindo tickets dos demais passageiros
		if(j == id) //Exceto o proprio ticket
			continue;
		//Espera ocupada
		//Segura a thread até que seja sua vez OU não cheio OU não saindo
		while((turns->at(j) != 0 && 
			 (turns->at(id) > turns->at(j) || (turns->at(id) == turns->at(j) && id > j) )) || carro->saindo || carro->cheio){

		}
	}
	//Seção Critica
	//Confere se o numero de pasageiros no carro é menor que a capacidade
	if(carro->numPassageiros <= carro->capacidade ){
		//Incrementa o numero de passageiros
		carro->numPassageiros.fetch_add(1);	
		if(carro->numPassageiros == carro->capacidade){//Se esse passageiro e o ultimo
			carro->cheio = true;
		}
	}
	//Zerando os tickets das threads que sairam da seção critica
	turns->at(id) = 0;

	//Seção não critica
	//Log
	Printer::start();
	Printer::append("O passageiro ");
	Printer::append(std::to_string(id));
	Printer::append(" entrou no carro");
	Printer::end();
//	Helpers::sync_cout << "O passageiro: " << id << " saiu do carro" << Helpers::sync_endl; //TODO COM ESPECIALIZACAO DE TEMPLATES SERIA ASSIM TAO BONITO

}
	
//Espera volta acabar, enquanto o tempod e volta do carro não terminar, continue dormindo
void Passageiro::esperaVoltaAcabar() {
	while (!carro->voltaAcabou) {
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}
//Saindo do carro
void Passageiro::saiDoCarro() {
	// Decrementa o numero de passageiros no carro (use a funcao fetch_add)
	carro->numPassageiros.fetch_add(-1);
	
	//Se esta for a ultima thread que sair do carro, não cheio
	if(carro->numPassageiros == 0){
		carro->cheio = false;
	}
	
	//Log
	Printer::start();
	Printer::append("O passageiro ");
	Printer::append(std::to_string(id));
	Printer::append(" saiu do carro");
	Printer::end();
}

void Passageiro::passeiaPeloParque() {
	// Dorme um tempo aleatorio
	std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
}

//Loop de vida do passageiro
void Passageiro::start(){
	while (1) {
		entraNoCarro(); 
		esperaVoltaAcabar();
		saiDoCarro(); 
		//Quando o parque fechar, acabe o programa
		if(carro->getParquePtr()->parqueFechado){
			std::exit(1);
		}
		passeiaPeloParque(); 
	}
}

//Passageiro run, execução.
void Passageiro::run() {
	//está sendo atribuido a t o endereço da thread passageiro
	//execução do metodo start
	t = std::thread(&Passageiro::start, this);
}
