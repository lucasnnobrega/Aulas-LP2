#include "../include/Mulher.h"

void Mulher::entrarNoBanheiro(Banheiro *b)
{
    this->banheiroAtual = b;
    b->e.lock();
    if((b->capacidadeTotal == b->numeroDeMulheres) 
	|| (b->numeroDeHomens > 0)
	|| (b->mulheresConsecutivas == b->maxConsecutivos))
	{
		//Mulher ao iniciar a espera
		sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou na fila " << sync_endl;
		b->nMulheresAtrasadas++;
		b->e.unlock();
		b->semMulher.lock();
    }
    
    b->numeroDeMulheres++;
	b->mulheresConsecutivas++;
	b->homensConsecutivos = 0;

	sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou no banheiro" << sync_endl;
    
    //SIGNAL 1
    if(b->nMulheresAtrasadas > 0)
    {
        b->nMulheresAtrasadas++;
        b->semMulher.unlock();
		b->e.unlock();//TESTE!!!!!!!!!!!!!!!!!!1
    }else{
        b->e.unlock();
    }

}

void Mulher::sairDoBanheiro(){
    //Mulher sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->numeroDeMulheres--;
	sync_cout << id << " \033[1;35m[MULHER]\033[0m Saiu do banheiro" << sync_endl;
	
	//SIGNAL 2
	if(banheiroAtual->mulheresConsecutivas == banheiroAtual->maxConsecutivos)
	{
		banheiroAtual->mulheresConsecutivas = 0;
		banheiroAtual->semHomem.unlock();
	}else{
		banheiroAtual->e.unlock();
	}
}

Mulher::Mulher(int id) : Pessoa(id){}