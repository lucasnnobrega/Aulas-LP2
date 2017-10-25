#include "../include/Mulher.h"

void Mulher::entrarNoBanheiro(Banheiro *b)
{
	this->banheiroAtual = b;
	sync_cout << "e l" << sync_endl;
    b->e.lock();
    if((b->capacidadeTotal == b->numeroDeMulheres) 
	|| (b->numeroDeHomens > 0)
	|| (b->mulheresConsecutivas == b->maxConsecutivos))
	{
		//Mulher ao iniciar a espera
		sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou na fila \n" << b->toString() <<  sync_endl;
		b->nMulheresAtrasadas++;
		sync_cout << "e u" << sync_endl;
		b->e.unlock();
		sync_cout << "m l" << sync_endl;
		b->semMulher.lock();
	}
	
    b->numeroDeMulheres++;
	b->mulheresConsecutivas++;
	b->homensConsecutivos = 0;

	sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou no banheiro \n" << b->toString() <<  sync_endl;
    
    //SIGNAL 1
    if(b->nMulheresAtrasadas > 0 && 
	   b->mulheresConsecutivas < b->maxConsecutivos &&
	   b->numeroDeMulheres < b->capacidadeTotal)
    {
		b->nMulheresAtrasadas--;
		sync_cout << "m u" << sync_endl;
		b->semMulher.unlock();
	//	b->e.unlock();//TESTE!!!!!!!!!!!!!!!!!!1
    }else{
		sync_cout << "e u" << sync_endl;
        b->e.unlock();
    }

}

void Mulher::sairDoBanheiro(){
	//Mulher sinaliza
	sync_cout << "e l" << sync_endl;
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->numeroDeMulheres--;
	sync_cout << id << " \033[1;35m[MULHER]\033[0m Saiu do banheiro \n" << banheiroAtual->toString() <<  sync_endl;
	
	//SIGNAL 2
	if(banheiroAtual->nHomensAtrasados > 0 && banheiroAtual->numeroDeMulheres == 0)
	{
		banheiroAtual->nHomensAtrasados--;
		sync_cout << "h u" << sync_endl;
		banheiroAtual->semHomem.unlock();
	}else if(banheiroAtual->nMulheresAtrasadas > 0 && banheiroAtual->mulheresConsecutivas < banheiroAtual->maxConsecutivos){
		banheiroAtual->nMulheresAtrasadas--;
		sync_cout << "m u" << sync_endl;
		banheiroAtual->semMulher.unlock();
	}else{
		sync_cout << "e u" << sync_endl;
		banheiroAtual->e.unlock();
	}
}

Mulher::Mulher(int id) : Pessoa(id){}
