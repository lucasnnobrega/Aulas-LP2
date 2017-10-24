#include "../include/Homem.h"

void Homem::entrarNoBanheiro(Banheiro* b){
	banheiroAtual = b;
	b->e.lock();

	sync_cout << id << " Passou do semaforo e" << sync_endl;
	assert(b != nullptr);


	//Se estiver cheio ou houver mulher dentro do banheiro, libere o semaforo 'e' e fique bloqueado em semHomem ate que alguem o acorde.
	if(b->get_numeroDeHomens() == b->get_capacidadeTotal() || b->get_numeroDeMulheres() > 0 || (b->get_homensConsecutivos() >= b->get_maxConsecutivos() && b->get_nMulheresAtrasadas() > 0) ){
		b->set_nHomensAtrasados(b->get_nHomensAtrasados() + 1);


		b->e.unlock();	
		//TODO Entra na fila auqui
		b->pessoasNaFila.push_back(id);
		sync_cout << id << " Desbloqueou e na linha 20!" << sync_endl;
		b->semHomem.lock();
		sync_cout << id << " Passou do semaforo semHomem" << sync_endl;
	}

	

	b->set_numeroDeHomens(b->get_numeroDeHomens()+1);

	//TODO remove da fila
	b->pessoasNaFila.erase(std::remove(b->pessoasNaFila.begin(), b->pessoasNaFila.end(), id), b->pessoasNaFila.end());
	b->set_mulheresConsecutivas(0);
	b->set_homensConsecutivos(b->get_homensConsecutivos() + 1);

	sync_cout << id << " Entrou no banheiro\n" << b->toString() << sync_endl;

	//Passe o bastão 
	if(b->get_numeroDeHomens() < b->get_capacidadeTotal()){
		if(b->get_homensConsecutivos() < b->get_maxConsecutivos() && b->get_nHomensAtrasados() > 0){
			b->set_nHomensAtrasados(b->get_nHomensAtrasados() - 1);
			sync_cout << id << " Quer passar a vez para Homens" << b->toString() << sync_endl;
			b->semHomem.unlock();						
		}
		else{
			b->e.unlock();
		}
	}
	else{
//		sync_cout << id << " Quer passar a vez para Ninguem\n" << b->toString() << sync_endl;
		b->e.unlock();
	}
	
}

void Homem::sairDoBanheiro(){	
	banheiroAtual->e.lock();

	banheiroAtual->set_numeroDeHomens(banheiroAtual->get_numeroDeHomens() - 1);

	sync_cout << id << " saiu do banheiro" << sync_endl;

	//SIGNAL
	if(banheiroAtual->get_nMulheresAtrasadas() > 0 && banheiroAtual->get_numeroDeHomens() == 0){
		banheiroAtual->set_nMulheresAtrasadas(banheiroAtual->get_nMulheresAtrasadas() - 1);
		sync_cout << id << " Quer passar a vez para Mulheres\n" << banheiroAtual->toString() << sync_endl;
		banheiroAtual->semMulher.unlock();
	}
	else if(banheiroAtual->get_nHomensAtrasados() > 0 && banheiroAtual->get_homensConsecutivos() < banheiroAtual->get_maxConsecutivos()){
		banheiroAtual->set_nHomensAtrasados(banheiroAtual->get_nHomensAtrasados() - 1);
		sync_cout << id << " Quer passar a vez para Homens\n" << banheiroAtual->toString() << sync_endl;
		banheiroAtual->semHomem.unlock();
	}else{
		banheiroAtual->e.unlock();	
	}
}

Homem::Homem(int n, Banheiro* b):Pessoa(n,b){}


