#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque(10);

    for (int i = 0; i < 10; i++) {
    	parque.addPassageiro(i);
    }

}
