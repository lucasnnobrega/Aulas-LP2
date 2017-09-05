/*
 * Carro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef CARRO_H_
#define CARRO_H_

class Parque;

class Carro {
public:
	static const int CAPACIDADE;
	/*
	Perde um aspecto da orientação a objeto pois a 
	variável estática é comum entre todos os objetos instanciados
	da classe tornando inviável a construção do carro 2
	*/
	static int numPassageiros;


	
	Carro(Parque *p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
	int getNVoltas();
	void run();

	void operator()()
	{
		run();
	}

private:
	int voltas;
	Parque *parque;
};

#endif /* CARRO_H_ */
