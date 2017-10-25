#ifndef BANHEIRO
#define BANHEIRO
#include <iostream>
#include "../include/ordered_mutex.h"
#include <string>
#include <sstream>

class Estabelecimento;

class Banheiro{

	
	int maxUtilizacao;
	int nUtilizacoes = 0;
 	int capacidadeTotal;//Numero maximo de pessoas que devem estar no banheiro
	int maxConsecutivos;//Numero maximo de pessoas do mesmo sexo entrando consecutivamente
	int numeroDeMulheres = 0;//Mulheres no banheiro
	int numeroDeHomens = 0;//Homens no banheiro
	int mulheresConsecutivas = 0;
	int homensConsecutivos = 0;

	int nMulheresAtrasadas = 0; //Mulheres esperando sua vez
	int nHomensAtrasados = 0; //Homens esperando sua vez
	
	ordered_mutex semHomem; //Semaforo do homem
	ordered_mutex semMulher; //Semaforo da mulher
	ordered_mutex e; //Semaforo regiao critca 
	
	Estabelecimento* estabelecimento;//Acesso ao contexto do estabelecimento	

public: 

    Banheiro(int capacidadeTotal, int maxConsecutivos, int maxUtilizacao);
	bool cheio();
	friend class Homem;
	friend class Mulher;
	friend class Pessoa;
	std::string toString();
};
#endif
