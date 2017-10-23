#include "../include/Estabelecimento.h"

void Estabelecimento::addPessoa(int sex, int id, Banheiro* banheiroInicial){
    if(sex == HOMEM){
        Pessoa *newPessoa = new Homem(id);
		newPessoa->banheiroAtual = banheiroInicial;
        pessoas.push_back(newPessoa);
    }else{
        Pessoa *newPessoa = new Mulher(id);
		newPessoa->banheiroAtual = banheiroInicial;
        pessoas.push_back(newPessoa);
    }
}

void Estabelecimento::set_banheiro(Banheiro* b){
	banheiro = b;
	sync_cout << "Banheiro setado" << sync_endl;
}

void Estabelecimento::iniciar(){
	sync_cout << "Liberando barreira" << sync_endl;
	Pessoa::barreira = true;
}

Estabelecimento::~Estabelecimento(){
	for(Pessoa* p : pessoas){
		sync_cout << "Destruindo pessoa de id " << p->getId();
		p->~Pessoa();
	}
}
