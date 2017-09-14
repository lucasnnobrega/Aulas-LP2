#include "include/Parque.h"
#include "include/Passageiro.h"

//namespace para escrever simplificadamente o tempo
using namespace std::chrono_literals;
using namespace Helpers;

//construtor de parque
Parque::Parque(int capacidade, int maxVoltas) : carro(this, capacidade, maxVoltas) {
	carro.run();
	std::this_thread::sleep_for(1s);
	parqueFechado = false; //iniciando parque
}

//destrutor de parque
Parque::~Parque() {
	for(Passageiro* e : passageiros){
	e->getThreadPtr()->join();
	//LOG
	Printer::start();
	Printer::append("Um passageiro saiu");
	Printer::end();

	}

	carro.join();
	
	//LOG
	Printer::start();
	Printer::append("O parque fechou");
	Printer::end();

}

int Parque::getNumPessoas(){
	return numPessoas;
}

//Ponteiro de turns, array de tickets que é compartilhado
std::vector<int>* Parque::getTurnsPtr(){
	return &turns;
}

//Adicionando passageiro 
void Parque::addPassageiro(int id){
	//Criando um novo passageiro, e passando o endereço do carro
	Passageiro* newPassageiro = new Passageiro(&carro, id);
	//aumentando o numero de turns
	turns.push_back(0);
	//iniciando a execução do passageiro
	newPassageiro->run();
	passageiros.push_back(newPassageiro);
}
