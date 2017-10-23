#include "../include/Homem.h"

void Homem::entrarNoBanheiro(Banheiro* b){
	this->banheiroAtual = b;
	b->e.lock();
	//Protocolo de entrada da seção critica
	//Homem espera sempre que:
	if((b->get_capacidadeTotal() == b->get_numeroDeMulheres() || b->get_capacidadeTotal() == b->get_numeroDeHomens()) 
	|| (b->get_numeroDeMulheres() > 0)
	|| (b->get_nMesmoSexo() == b->get_maxConsecutivos()))
	{
		//Homem ao iniciar a espera
		sync_cout << id << " Entrou na fila " << sync_endl;
		b->set_nHomensAtrasados((b->get_nHomensAtrasados()+1));
		b->e.unlock();
		b->semHomem.lock();
	}

	//Após a entrada no banheiro, imediatamente
	b->set_numeroDeHomens((b->get_numeroDeHomens()+1));
	b->set_nMesmoSexo((b->get_nMesmoSexo()+1));

	sync_cout << id << " Entrou no banheiro; nMesmoSexo: " << b->get_nMesmoSexo() << " , " << b->get_maxConsecutivos() << sync_endl;
	
	//SIGNAL 1
	if(b->get_nHomensAtrasados() > 0)
	{
		b->set_nHomensAtrasados((b->get_nHomensAtrasados()-1));
		b->semHomem.unlock();
	}else{
		b->e.unlock();
	}

}

void Homem::sairDoBanheiro(){
	//Homem sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->set_numeroDeHomens(banheiroAtual->get_numeroDeHomens()-1);
	sync_cout << id <<  " Saiu do banheiro" << sync_endl;
	
	//SIGNAL 2
	if(banheiroAtual->get_nMesmoSexo() == banheiroAtual->get_maxConsecutivos())
	{
		banheiroAtual->set_nMesmoSexo(0);
		banheiroAtual->semMulher.unlock();
	}else{
		banheiroAtual->e.unlock();
	}
}

Homem::Homem(int n):Pessoa(n){}


