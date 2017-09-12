#include <iostream>
#include <vector>
#include <exception>
#include <thread>
#include "include/Parque.h"
#include "include/Carro.h"
#include "include/Passageiro.h"

using namespace std;

int main() {
	try{
		Parque parque(5);
   		for (int i = 0; i < 10; i++) {
    		parque.addPassageiro(i);
    	}
	}
	catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}

}
