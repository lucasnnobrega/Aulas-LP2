#include <iostream>
#include <vector>
#include <thread>
#include "include/Parque.h"

using namespace std;

int main() {
	Parque parque(5);
	for(int i = 0; i <= 10; i++){
		parque.addCliente(i);
	}	

	try{
		parque.runCarro();
		std::this_thread::sleep_for(std::chrono::seconds(2));
		parque.runClientes();
	}
	catch(const Done& done){
		return 0;
	}
}
