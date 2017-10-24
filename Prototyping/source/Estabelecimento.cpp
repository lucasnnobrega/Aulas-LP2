#include "../include/Estabelecimento.h"

void Estabelecimento::addPessoa(int sex, int id, Banheiro* banheiroInicial){
    if(sex == HOMEM){
        Pessoa *newPessoa = new Homem(id, banheiroInicial);
        pessoas.push_back(newPessoa);
    }else{
        Pessoa *newPessoa = new Mulher(id, banheiroInicial);
        pessoas.push_back(newPessoa);
    }
}

void Estabelecimento::set_banheiro(Banheiro* b){
	banheiro = b;
	sync_cout << "Banheiro setado" << sync_endl;
}

void Estabelecimento::iniciar(){
	sync_cout << "Liberando barreira" << sync_endl;
}

Estabelecimento::~Estabelecimento(){
	for(Pessoa* p : pessoas){
		sync_cout << "Destruindo pessoa de id " << p->getId();
		p->~Pessoa();
	}
}
