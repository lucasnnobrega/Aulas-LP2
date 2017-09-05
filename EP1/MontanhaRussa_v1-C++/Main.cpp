#include <iostream>
#include <vector>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque;
	Carro carro(&parque);
	Passageiro *passageiros[10];

    for (int i = 0; i < 10; i++) {
    	passageiros[i] = new Passageiro(i, &carro, &parque);
    	parque.addPassageiro(passageiros[i]);
    }

    carro.start();
    for (auto &p : parque.getPassageiros()) p->start();

    carro.join();
    for (auto &p : parque.getPassageiros()) p->join();

    for (int i = 0; i < 10; i++) {
    	delete passageiros[i];
    }

	return 0;
}
