#include "../include/Homem.h"

void Homem::entrarNoBanheiro(Banheiro* b){
	banheiroAtual = b;
	b->e.lock();
	//Protocolo de entrada da seção critica
	//Homem espera sempre que:
	if((b->capacidadeTotal == b->numeroDeHomens) 
	|| (b->numeroDeMulheres > 0)
	|| (b->homensConsecutivos >= b->maxConsecutivos))
	{
		//Homem ao iniciar a espera
		sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou na fila" << sync_endl;
		b->nHomensAtrasados++;
		b->e.unlock();
		b->semHomem.lock();
	}

	//Após a entrada no banheiro, imediatamente
	b->numeroDeHomens++;
	b->homensConsecutivos++;
	b->mulheresConsecutivas = 0;

	sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou no banheiro" << sync_endl;
	
	//SIGNAL 1
	if(b->nHomensAtrasados > 0 &&
	   b->homensConsecutivos < b->maxConsecutivos &&
	   b->numeroDeHomens < b->capacidadeTotal)
	{
		b->nHomensAtrasados--;
		b->semHomem.unlock();
	}else{
		b->e.unlock();
	}

}

void Homem::sairDoBanheiro(){
	//Homem sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->numeroDeHomens--;
	sync_cout << id <<  " \033[1;31m[HOMEM]\033[0m Saiu do banheiro" << sync_endl;
	
	//SIGNAL 2
	if(banheiroAtual->homensConsecutivos >= banheiroAtual->maxConsecutivos)
	{
		banheiroAtual->homensConsecutivos = 0;
		banheiroAtual->semMulher.unlock();
	}else{
		banheiroAtual->e.unlock();
	}
}

Homem::Homem(int id):Pessoa(id){}


