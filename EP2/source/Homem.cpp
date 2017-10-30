#include "../include/Homem.h"

#define SAIU_DO_BANHEIRO 1
#define ENTROU_NO_BANHEIRO 2
#define SAIU_DA_FILA 3
#define ENTROU_NA_FILA 4
#define DANCANDO_NA_BOATE 5

//Define's semaphores 1 lock and 0 is unlock
#define SEM_H 10
#define SEM_M 20
#define SEM_E 30

void Homem::entrarNoBanheiro(Banheiro* b){
	banheiroAtual = b;
	//sync_cout << "e l" << sync_endl;
	b->e.lock();
	Logger::log(1 , SEM_E);
	//Protocolo de entrada da seção critica
	//Homem espera sempre que:
	if(b->nUtilizacoes > b->maxUtilizacao){
	//	sync_cout << "e u" << sync_endl;
		b->e.unlock();
		Logger::log(0 , SEM_E);
	}else if((b->capacidadeTotal == b->numeroDeHomens) 
			|| (b->numeroDeMulheres > 0)
			|| (b->homensConsecutivos == b->maxConsecutivos)
			||(b->nUtilizacoes + 1 >= b->maxUtilizacao) )
			{
				 
				//Homem ao iniciar a espera
				sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou na fila \n" << b->toString() << sync_endl;
				Logger::log(ENTROU_NA_FILA, id);				
				b->nHomensAtrasados++;
				
				//sync_cout << "e u" << sync_endl;
				b->e.unlock();
				Logger::log(0 , SEM_E);				
				//sync_cout << "h l" << sync_endl;

				b->semHomem.lock();
				Logger::log(1 , SEM_H);
				
			}

	
	//Após a entrada no banheiro, imediatamente
	b->nUtilizacoes++;
	b->numeroDeHomens++;
	b->homensConsecutivos++;
	b->mulheresConsecutivas = 0;

	sync_cout << id << " \033[1;31m[HOMEM] \033[0mEntrou no banheiro \n" <<  b->toString() << sync_endl;
	Logger::log(ENTROU_NO_BANHEIRO, id);
	
	//SIGNAL 1
	if(b->nHomensAtrasados > 0 &&
	   b->homensConsecutivos < b->maxConsecutivos &&
	   b->numeroDeHomens < b->capacidadeTotal)
	{
		b->nHomensAtrasados--;
	//	sync_cout << "h u" << sync_endl;
		b->semHomem.unlock();
		Logger::log(0, SEM_H);
		
	}else{
	//	sync_cout << "e u" << sync_endl;
		b->e.unlock();
		Logger::log(0, SEM_E);
		
	}

}

void Homem::sairDoBanheiro(){
	//Homem sinaliza
	//sync_cout << "e l" << sync_endl;
	banheiroAtual->e.lock();//P(e)
	Logger::log(1, SEM_E);
	banheiroAtual->numeroDeHomens--;
	sync_cout << id <<  " \033[1;31m[HOMEM]\033[0m Saiu do banheiro \n" << banheiroAtual->toString() << sync_endl;
	Logger::log(SAIU_DO_BANHEIRO, id);

	//SIGNAL 2
	if(banheiroAtual->nMulheresAtrasadas > 0 && 
		banheiroAtual->numeroDeHomens == 0 && 
		(banheiroAtual->nUtilizacoes < banheiroAtual->maxUtilizacao))
	{
		banheiroAtual->nMulheresAtrasadas--;
	//	sync_cout << "m u" << sync_endl;
		banheiroAtual->semMulher.unlock();
		Logger::log(0,SEM_M);

	}else if(banheiroAtual->nHomensAtrasados > 0 && 
		banheiroAtual->homensConsecutivos < banheiroAtual->maxConsecutivos ){
		
		banheiroAtual->nHomensAtrasados--;
	//	sync_cout << "h u" << sync_endl;	
		banheiroAtual->semHomem.unlock();
		Logger::log(0,SEM_H);
	}
	else{
	//	sync_cout << "e u" << sync_endl;
		banheiroAtual->e.unlock();
		Logger::log(0,SEM_E);
	}
}

Homem::Homem(int id):Pessoa(id){}


