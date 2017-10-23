#include "../include/Homem.h"

void Homem::entrarNoBanheiro(Banheiro* b){
	this->banheiroAtual = b;
	sync_cout << "Homem com id " << id << "tentou entrar" << sync_endl;
	b->e.lock();
	//Protocolo de entrada da seção critica
	//Homem espera sempre que:
	if((b->get_capacidadeTotal() == b->get_numeroDeMulheres() || b->get_capacidadeTotal() == b->get_numeroDeHomens()) 
	|| (b->get_numeroDeMulheres() > 0)
	|| (b->get_nMesmoSexo() == b->get_maxConsecutivos()))
	{
		//Homem ao iniciar a espera
		b->set_nHomensAtrasados((b->get_nHomensAtrasados()+1));
		b->e.unlock();
		b->semHomem.lock();
	}

	//Após a entrada no banheiro, imediatamente
	b->set_numeroDeHomens((b->get_numeroDeHomens()+1));
	b->set_nMesmoSexo((b->get_nMesmoSexo()+1));

	sync_cout << "O homem com id " <<  id << " entrou" << sync_endl;
	
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
	sync_cout << "O homem com id " << id << " saiu" << sync_endl;

	//Homem sinaliza
	banheiroAtual->e.lock();//P(e)
	banheiroAtual->set_numeroDeHomens(banheiroAtual->get_numeroDeHomens()-1);
	
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


