#include "../include/Homem.h"

int Homem::entrarNoBanheiro(Banheiro* b){
	banheiroAtual = b;
	//sync_cout << "e l" << sync_endl;
	Logger::log(BLOQUEOU_SEM, SEM_E);
	b->e.lock();
	//Protocolo de entrada da seção critica
	//Homem espera sempre que:
	if((b->capacidadeTotal == b->numeroDeHomens) 
			|| (b->numeroDeMulheres > 0)
			|| (b->homensConsecutivos == b->maxConsecutivos)
			||(b->nUtilizacoes + 1 >= b->maxUtilizacao) )
			{
				b->nHomensAtrasados++;

				Logger::log(ENTROU_NA_FILA, id);	
				sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou na fila \n" << b->toString() << sync_endl;
				
				Logger::log(LIBEROU_SEM, SEM_E);
				b->e.unlock();

				Logger::log(BLOQUEOU_SEM, SEM_H);
				b->semHomem.lock();
				if(b->nUtilizacoes >= b->maxUtilizacao){
					return 0;
				}
	}

	
	//Após a entrada no banheiro, imediatamente
	b->nUtilizacoes++;
	b->numeroDeHomens++;
	b->homensConsecutivos++;
	b->inUse = true;
	b->mulheresConsecutivas = 0;

	Logger::log(ENTROU_NO_BANHEIRO, id);
	sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou no banheiro \n" <<  b->toString() << sync_endl;
	
	//SIGNAL 1
	if(b->nHomensAtrasados > 0 &&
	   b->homensConsecutivos < b->maxConsecutivos &&
	   b->numeroDeHomens < b->capacidadeTotal)
	{
		b->nHomensAtrasados--;

		Logger::log(LIBEROU_SEM, SEM_H);
		b->semHomem.unlock();
	}else{
		Logger::log(LIBEROU_SEM, SEM_E);
		b->e.unlock();
	}
	return 0;
}

void Homem::sairDoBanheiro(){
	//Homem sinaliza
	Logger::log(BLOQUEOU_SEM, SEM_E);
	banheiroAtual->e.lock();

	banheiroAtual->numeroDeHomens--;
	
	Logger::log(SAIU_DO_BANHEIRO, id);
	sync_cout << id <<  " \033[1;31m[HOMEM]\033[0m Saiu do banheiro \n" << banheiroAtual->toString() << sync_endl;

	if(banheiroAtual->numeroDeHomens == 0 && banheiroAtual->nUtilizacoes + 1 > banheiroAtual->maxUtilizacao){
		Logger::end();
		std::exit(0);
	}
	
	//SIGNAL 2
	if(banheiroAtual->nMulheresAtrasadas > 0 && 
		banheiroAtual->numeroDeHomens == 0 && 
		(banheiroAtual->nUtilizacoes + 1 <=  banheiroAtual->maxUtilizacao))
	{
		banheiroAtual->nMulheresAtrasadas--;

		Logger::log(LIBEROU_SEM, SEM_M);
		banheiroAtual->semMulher.unlock();

	}else if(banheiroAtual->nHomensAtrasados > 0 && 
		banheiroAtual->homensConsecutivos < banheiroAtual->maxConsecutivos &&
		banheiroAtual->nUtilizacoes + 1 <= banheiroAtual->maxUtilizacao
		){
		
		banheiroAtual->nHomensAtrasados--;

		Logger::log(LIBEROU_SEM, SEM_H);
		banheiroAtual->semHomem.unlock();
	}
	else{
		Logger::log(LIBEROU_SEM, SEM_E);
		banheiroAtual->e.unlock();
	}
}

Homem::Homem(int id):Pessoa(id){}


