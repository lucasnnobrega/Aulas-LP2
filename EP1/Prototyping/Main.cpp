#include <iostream>
#include <vector>
#include <exception>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "./include/helper.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	//Construindo o parque, (maximospassageiros, maximodevoltas)
	Parque parque(5, 2);
	for (int i = 0; i < 10; i++) {
   		parque.addPassageiro(i);
   	}
}
