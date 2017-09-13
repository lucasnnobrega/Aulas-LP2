#include <iostream>
#include <vector>
#include <exception>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	Parque parque(5, 3);
	for (int i = 0; i < 100; i++) {
   		parque.addPassageiro(i);
   	}
}
