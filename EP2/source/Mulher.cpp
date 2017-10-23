#include "../include/Mulher.h"

void Mulher::entrarNoBanheiro(Banheiro *b)
{
    this->banheiroAtual = b;
    b->e.lock();
    if((b->get_capacidadeTotal() == b->get_numeroDeMulheres() || b->get_capacidadeTotal() == b->get_numeroDeHomens()) 
	|| (b->get_numeroDeHomens() > 0)
	|| (b->get_nMesmoSexo() == b->get_maxConsecutivos())
	{
		//Homem ao iniciar a espera
		b->set_nMulheresAtrasadas((b->get_nMulheresAtrasadas()+1));
		b->e.unlock();
		b->semMulher.lock();
    }
    
    b->set_numeroDeMulheres(b->get_numeroDeMulheres()+1);
    b->set_nMesmoSexo(b->get_nMesmoSexo()+1);
    
    //SIGNAL 1
    if(b->get_nHomensAtrasados() > 0)
    {
        b->set_nHomensAtrasados(b->get_nHomensAtrasados()+1);
        b->semMulher.unlock();
    }else{
        b->e.unlock();
    }

    
    //std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    //this->sairDoBanheiro(b);
}

void Mulher::sairDoBanheiro(){
    //Mulher sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->set_numeroDeMulheres(banheiroAtual->get_numeroDeMulheres()-1);
	
	//SIGNAL 2
	if(banheiroAtual->get_nMesmoSexo() == banheiroAtual->get_maxConsecutivos())
	{
		banheiroAtual->set_nMesmoSexo(0);
		banheiroAtual->semHomem.unlock();
	}else{
		banheiroAtual->e.unlock();
	}
}