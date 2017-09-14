#include <iostream>
#include <vector>
#include <exception>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "./include/helper.h"
#include "include/Passageiro.h"

using namespace std;

int main(int argc, char** argv) {
	//Construindo o parque, (maximospassageiros, maximodevoltas)
	if(argc == 3){
		Passageiro::minSleep = std::stoi(std::string(argv[1]));
		Passageiro::maxSleep = std::stoi(std::string(argv[2]));;
	}
	Parque parque(5, 10);
	for (int i = 0; i < 10; i++) {
   		parque.addPassageiro(i);
   	}
}
