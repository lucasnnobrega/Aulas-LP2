#include "../include/Mulher.h"

void Mulher::entrarNoBanheiro(Banheiro* b){
	banheiroAtual = b;
	b->e.lock();

	sync_cout << id << " Passou do semaforo e" << sync_endl;
	assert(b != nullptr);


	//Se estiver cheio ou houver mulher dentro do banheiro, libere o semaforo 'e' e fique bloqueado em semMulher ate que alguem o acorde.
	if(b->get_numeroDeHomens() > 0 || b->get_numeroDeMulheres() == b->get_capacidadeTotal() || ((b->get_mulheresConsecutivas() >= b->get_maxConsecutivos()) && b->get_nHomensAtrasados() > 0) ){
		b->set_nMulheresAtrasadas(b->get_nMulheresAtrasadas() + 1);
		b->e.unlock();	
		//TODO Entra na fila auqui
		b->pessoasNaFila.push_back(id);
		sync_cout << id << " Desbloqueou e na linha 20!" << sync_endl;
		b->semMulher.lock();
		sync_cout << id << " Passou do semaforo semMulher" << sync_endl;
	}

	b->set_numeroDeMulheres(b->get_numeroDeMulheres()+1);

	//TODO remove da fila
	b->pessoasNaFila.erase(std::remove(b->pessoasNaFila.begin(), b->pessoasNaFila.end(), id), b->pessoasNaFila.end());
	b->set_homensConsecutivos(0);
	b->set_mulheresConsecutivas(b->get_mulheresConsecutivas() + 1);

	sync_cout << id << " Entrou no banheiro\n" << b->toString() << sync_endl;

	//Passe o bastão 
	if(b->get_numeroDeMulheres() < b->get_capacidadeTotal()){
		if(b->get_mulheresConsecutivas() < b->get_maxConsecutivos() && b->get_nMulheresAtrasadas() > 0){
			b->set_nMulheresAtrasadas(b->get_nMulheresAtrasadas() - 1);
			sync_cout << id << " Quer passar a vez para Mulheres\n" << b->toString() << sync_endl;
			b->semMulher.unlock();						
		}
		else{
			b->e.unlock();
		}
	}
	else{
		sync_cout << id << " Quer passar a vez para Mulheres\n" << b->toString() << sync_endl;
		b->e.unlock();
	}
	
}

void Mulher::sairDoBanheiro(){	
	banheiroAtual->e.lock();

	banheiroAtual->set_numeroDeMulheres(banheiroAtual->get_numeroDeMulheres() - 1);

	sync_cout << id << " saiu do banheiro" << sync_endl;

	//SIGNAL
	if(banheiroAtual->get_nHomensAtrasados() > 0 && banheiroAtual->get_numeroDeMulheres() == 0){
		banheiroAtual->set_nHomensAtrasados(banheiroAtual->get_nHomensAtrasados() - 1);
		sync_cout << id << " Quer passar a vez para Mulheres\n" << banheiroAtual->toString() << sync_endl;
		banheiroAtual->semHomem.unlock();
	}
	else if(banheiroAtual->get_nMulheresAtrasadas() > 0 && banheiroAtual->get_mulheresConsecutivas() < banheiroAtual->get_maxConsecutivos()){
		banheiroAtual->set_nMulheresAtrasadas(banheiroAtual->get_nMulheresAtrasadas() - 1);
		sync_cout << id << " Quer passar a vez para Mulheres\n" << banheiroAtual->toString() << sync_endl;
		banheiroAtual->semMulher.unlock();
	}else{
		banheiroAtual->e.unlock();	
	}
}

Mulher::Mulher(int n, Banheiro* b):Pessoa(n,b){}


