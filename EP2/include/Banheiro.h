#ifndef BANHEIRO
#define BANHEIRO
#include <iostream>
#include <mutex>

#include "../include/Homem.h"
#include "../include/Mulher.h"

class estabelecimento;

class Banheiro{
	int capacidadeTotal;//Numero maximo de pessoas que devem estar no banheiro
	int maxConsecutivos;//Numero maximo de pessoas do mesmo sexo entrando consecutivamente
	int numeroDeMulheres = 0;//Mulheres no banheiro
	int numeroDeHomens = 0;//Homens no banheiro
	int nMesmoSexo = 0; //Numero de pessoas do mesmo sexo que entraram consecutivamente 

	int nMulheresAtrasadas = 0; //Mulheres esperando sua vez
	int nHomensAtrasados = 0; //Homens esperando sua vez

	std::mutex semHomem; //Semaforo do homem
	std::mutex semMulher; //Semaforo da mulher
	std::mutex e; //Semaforo regiao critca 

	Estabelecimento* estabelecimento;//Acesso ao contexto do estabelecimento

    public: 
    Banheiro(int capcidadeTotal, maxConsecutivos);
	bool cheio();
	friend class Homem;
	friend class Mulher;
  };
#endif
