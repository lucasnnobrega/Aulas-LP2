#ifndef BANHEIRO
#define BANHEIRO
#include <iostream>
#include <mutex>

class Estabelecimento;

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
	int get_capacidadeTotal();//Numero maximo de pessoas que devem estar no banheiro
	int get_maxConsecutivos();//Numero maximo de pessoas do mesmo sexo entrando consecutivamente
	int get_numeroDeMulheres();//Mulheres no banheiro
	int get_numeroDeHomens();//Homens no banheiro
	int get_nMesmoSexo(); //Numero de pessoas do mesmo sexo que entraram consecutivamente 
	int get_nMulheresAtrasadas(); //Mulheres esperando sua vez
	int get_nHomensAtrasados(); //Homens esperando sua vez
	
	void set_capacidadeTotal(int a);//Numero maximo de pessoas que devem estar no banheiro
	void set_maxConsecutivos(int a);//Numero maximo de pessoas do mesmo sexo entrando consecutivamente
	void set_numeroDeMulheres(int a);//Mulheres no banheiro
	void set_numeroDeHomens(int a);//Homens no banheiro
	void set_nMesmoSexo(int a); //Numero de pessoas do mesmo sexo que entraram consecutivamente 
	
	void set_nMulheresAtrasadas(int a); //Mulheres esperando sua vez
	void set_nHomensAtrasados(int a); //Homens esperando sua vez
	
    Banheiro(int capacidadeTotal, int maxConsecutivos);
	bool cheio();
	friend class Homem;
	friend class Mulher;
	friend class Pessoa;

};
#endif
