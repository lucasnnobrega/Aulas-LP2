#include "../include/Estabelecimento.h"

int main(){
	Banheiro meuBanheiro(5, 1);
	sync_cout << "Banheiro criado" << sync_endl;
	Estabelecimento meuEstabelecimento;
	std::cout << "Estabelecimento criado" << std::endl;

	meuEstabelecimento.set_banheiro(&meuBanheiro);
/*
	int id = 0;
	while(id++ < 5){
		std::cout << "Homem " << id << " criado " << std::endl;
		meuEstabelecimento.addPessoa(HOMEM, id, &meuBanheiro);
	}
	while(id++ < 10){
		std::cout << "Mulher " << id << " criado " << std::endl;
		meuEstabelecimento.addPessoa(MULHER, id, &meuBanheiro);
	}
	*/
	meuEstabelecimento.addPessoa(HOMEM, 1, &meuBanheiro);
	meuEstabelecimento.addPessoa(HOMEM, 2, &meuBanheiro);
	meuEstabelecimento.addPessoa(MULHER, 3, &meuBanheiro);
	meuEstabelecimento.addPessoa(MULHER, 4, &meuBanheiro);
	char a;
	std::cin >> a;
	meuEstabelecimento.iniciar();

}
