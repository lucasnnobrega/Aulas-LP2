#include <iostream>
#include "Pessoa.h"
#include "./Banheiro.h"
#include <vector>

#define HOMEM 1
#define MULHER 2

#define MAX_PESSOAS_BANHEIRO 5
#define MAX_PESSOAS_TOTAL 10

class Pessoa;

class Estabelecimento{
    Banheiro banheiro(MAX_PESSOAS_BANHEIRO);
	std::vector<Pessoa*> pessoas;
	public:
	addPessoa(int sex);
};
