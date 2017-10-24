#include "../include/Mulher.h"

Mulher::Mulher(int id) : Pessoa(id){

}

void Mulher::entrarNoBanheiro(Banheiro *b)
{
    this->banheiroAtual = b;
    b->e.lock();
    if((b->get_capacidadeTotal() == b->get_numeroDeMulheres() || b->get_capacidadeTotal() == b->get_numeroDeHomens()) 
	|| (b->get_numeroDeHomens() > 0)
	|| (b->get_nMesmoSexo() == b->get_maxConsecutivos()))
	{
		//Mulher ao iniciar a espera
		sync_cout << id << " Entrou na fila " << sync_endl;
		b->set_nMulheresAtrasadas((b->get_nMulheresAtrasadas()+1));
		b->e.unlock();
		b->semMulher.lock();
    }
    
    b->set_numeroDeMulheres(b->get_numeroDeMulheres()+1);
    b->set_nMesmoSexo(b->get_nMesmoSexo()+1);

	sync_cout << id << " Entrou no banheiro" << sync_endl;
    
    //SIGNAL 1
    if(b->get_nHomensAtrasados() > 0)
    {
        b->set_nHomensAtrasados(b->get_nHomensAtrasados()+1);
        b->semMulher.unlock();
    }else{
        b->e.unlock();
    }

}

void Mulher::sairDoBanheiro(){
    //Mulher sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->set_numeroDeMulheres(banheiroAtual->get_numeroDeMulheres()-1);
	sync_cout << id << " Saiu do banheiro" << sync_endl;
	
	//SIGNAL 2
	if(banheiroAtual->get_nMesmoSexo() == banheiroAtual->get_maxConsecutivos())
	{
		banheiroAtual->set_nMesmoSexo(0);
		banheiroAtual->semHomem.unlock();
	}else{
		banheiroAtual->e.unlock();
	}
}
