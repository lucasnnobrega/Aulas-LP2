#include "./include/sync_printer.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

struct Barbeiro{
	int id;
	thread* t;
	public:
	Barbeiro(int id_) : id(id_){}
	~Barbeiro(){
		if(t->joinable()){
			t->join();
		}
	};
	void run();
};

struct Cliente{
	int id;
	thread* t;
	public:
	Cliente(int id_) : id(id_){}
	~Cliente(){
		if(t->joinable()){
			t->join();
		}
	}
	void run();
};


struct Barbearia{
	mutex cvMutex;
	condition_variable cvBarbeiroLivre;
	condition_variable cvClienteEsperando;
	condition_variable saida; 

	int barbeirosLivres = 0;
	int clienteEsperando = 0;
	public:
	void solicitarCadeira(Cliente* which){
		unique_lock<mutex> lock(cvMutex);
		clienteEsperando++;
		while(barbeirosLivres == 0){
			cvBarbeiroLivre.wait(lock);
		}
		barbeirosLivres--;
		//TODO: Make sure the right client is woken up 
		sync_cout << which->id << " Sentou" << sync_endl;
		cvClienteEsperando.notify_one();
		saida.wait(lock);
	}
	void finalizarCorte(){
		lock_guard<mutex> lock(cvMutex);
		saida.notify_one();
	}
	void proximoCliente(){
		unique_lock<mutex> lock(cvMutex);
		barbeirosLivres++;
		while(clienteEsperando == 0){
			cvClienteEsperando.wait(lock);
		}
		clienteEsperando--;
		cvBarbeiroLivre.notify_one();	
	}
};

Barbearia barbearia;
vector <Barbeiro*> barbeiros;
vector <Cliente*> clientes;

void Cliente::run(){
	t = new thread([&]{
		while(1){
			barbearia.solicitarCadeira(this);
			sync_cout << id << " Foi embora" << sync_endl;
			this_thread::sleep_for(3s);
		}
	});
}

void Barbeiro::run(){
	t = new thread([&]{
		while(1){
			barbearia.proximoCliente();
			this_thread::sleep_for(1s);
			barbearia.finalizarCorte();
		}		
	});
}

#define MAXB 3
#define MAXC 10

int main(){
	for(int i = 0; i < MAXB; i++){
		barbeiros.push_back( new Barbeiro(i));
	}
	for(int i = 0; i < MAXC; i++){
		clientes.push_back(new Cliente(i));
	}
	for(auto& e : barbeiros){
		e->run();
	}	
	for(auto& e : clientes){
		e->run();
	}	
	for(auto e : barbeiros){
		e->~Barbeiro();
	}	
}	
