#include "../include/Estabelecimento.h"

int main(){
	Banheiro meuBanheiro(4, 5);
	sync_cout << "Banheiro criado" << sync_endl;
	Estabelecimento meuEstabelecimento;
	sync_cout << "Estabelecimento criado" << sync_endl;

	meuEstabelecimento.set_banheiro(&meuBanheiro);

	meuEstabelecimento.addPessoa(HOMEM, 1, &meuBanheiro);
	meuEstabelecimento.addPessoa(HOMEM, 2, &meuBanheiro);
	meuEstabelecimento.addPessoa(HOMEM, 3, &meuBanheiro);
	meuEstabelecimento.addPessoa(HOMEM, 4, &meuBanheiro);

	meuEstabelecimento.addPessoa(MULHER, 5, &meuBanheiro);
	meuEstabelecimento.addPessoa(MULHER, 6, &meuBanheiro);
	meuEstabelecimento.addPessoa(MULHER, 7, &meuBanheiro);
	meuEstabelecimento.addPessoa(MULHER, 8, &meuBanheiro);


}
