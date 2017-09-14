#ifndef CARRO_H_
#define CARRO_H_
#include <atomic>
#include <thread>
#include "helper.h"
#include <utility>
#include <vector>

#define DURACAO_DA_VOLTA 200

class Parque;

class Carro {
	std::atomic<int> numPassageiros{0}; //Numero de passageiros ate agora
	bool voltaAcabou;//A volta acabou?
	bool saindo;//Os passageiros estão desembarcando?
	bool cheio;//O carro está cheio?
	int voltas;//Numero de voltas ate agora
	int maxVoltas;//Numero maximo de voltas ate encerrar o parque
	int capacidade;//Capacidade maxima do parque
	Parque *parque;//Ponteiro para o parque que possui carro como membro
	std::thread t;//Thread com loop de acão do carro
	std::vector<int>* turns;//Ponteiro para o array de inteiros utilizado no algoritmo da padaria

	public:

	Carro(Parque *p, int capacidade, int maxVoltas_);//Construtor
	~Carro();//Destrutor
	void join();//Se t.joinable(), t.join()

	void esperaEncher();//Espera ocupada 
	void daUmaVolta();//Dorme um tempo fixo
	void esperaEsvaziar();//Espera ocupada 
	bool joinable();//t.joinable()

	int getNVoltas();//Numero de voltas dados ate o momento
	Parque* getParquePtr();//Retorna ponteiro para o parque que tem esse carro como membro

	void run();//Começa a thread com start() como argumento
	void start();//Loop de atividade do carro

	friend class Passageiro;//Dá a passageiros acesso aos membros privados do carro
};

#endif /* CARRO_H_ */
