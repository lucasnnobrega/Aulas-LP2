#include "../include/Mulher.h"

#define SAIU_DO_BANHEIRO 1
#define ENTROU_NO_BANHEIRO 2
#define SAIU_DA_FILA 3
#define ENTROU_NA_FILA 4
#define DANCANDO_NA_BOATE 5

//Define's semaphores 1 lock and 0 is unlock
#define SEM_H 10
#define SEM_M 20
#define SEM_E 30

void Mulher::entrarNoBanheiro(Banheiro *b){
	banheiroAtual = b;
	//sync_cout << "e l" << sync_endl;
	b->e.lock();
	Logger::log(1 , SEM_E);
	//Protocolo de entrada da seção critica
	//Mulher espera sempre que:
	if(b->nUtilizacoes > b->maxUtilizacao){
		//sync_cout << "e u" << sync_endl;
		b->e.unlock();
		Logger::log(0 , SEM_E);
	}else if((b->capacidadeTotal == b->numeroDeMulheres) 
			|| (b->numeroDeHomens > 0)
			|| (b->mulheresConsecutivas == b->maxConsecutivos)
			||	 (b->nUtilizacoes + 1 >= b->maxUtilizacao))
			{
	
				//Mulher ao iniciar a espera
				sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou na fila \n" << b->toString() <<  sync_endl;
				Logger::log(ENTROU_NA_FILA, id);
				b->nMulheresAtrasadas++;
				
				//sync_cout << "e u" << sync_endl;
				b->e.unlock();
				Logger::log(0 , SEM_E);				
				//sync_cout << "m l" << sync_endl;

				b->semMulher.lock();
				Logger::log(1 , SEM_M);
				
	        }
			
	//Após a entrada no banheiro, imediatamente
	b->nUtilizacoes++;
    b->numeroDeMulheres++;
	b->mulheresConsecutivas++;
	b->homensConsecutivos = 0;


	sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou no banheiro \n" << b->toString() <<  sync_endl;
	Logger::log(ENTROU_NO_BANHEIRO, id);
	
    //SIGNAL 1
    if(b->nMulheresAtrasadas > 0 && 
	   b->mulheresConsecutivas < b->maxConsecutivos &&
	   b->numeroDeMulheres < b->capacidadeTotal)
    {
		b->nMulheresAtrasadas--;
		//sync_cout << "m u" << sync_endl;
		b->semMulher.unlock();
		Logger::log(0, SEM_M);
		
	//	b->e.unlock();//TESTE!!!!!!!!!!!!!!!!!!1
    }else{
		//sync_cout << "e u" << sync_endl;
		b->e.unlock();
		Logger::log(0, SEM_E);
		
    }

}

void Mulher::sairDoBanheiro(){
	//Mulher sinaliza
	//sync_cout << "e l" << sync_endl;
	banheiroAtual->e.lock();//P(e)
	Logger::log(1, SEM_E);
	banheiroAtual->numeroDeMulheres--;
	sync_cout << id << " \033[1;35m[MULHER]\033[0m Saiu do banheiro \n" << banheiroAtual->toString() <<  sync_endl;
	Logger::log(SAIU_DO_BANHEIRO, id);

	//SIGNAL 2
	if(banheiroAtual->nHomensAtrasados > 0 && 
		banheiroAtual->numeroDeMulheres == 0 && 
		(banheiroAtual->nUtilizacoes <= banheiroAtual->maxUtilizacao))
	{
		banheiroAtual->nHomensAtrasados--;
	//	sync_cout << "h u" << sync_endl;
		banheiroAtual->semHomem.unlock();
		Logger::log(0,SEM_H);		

	}else if(banheiroAtual->nMulheresAtrasadas > 0 && 
		banheiroAtual->mulheresConsecutivas < banheiroAtual->maxConsecutivos){
		
		banheiroAtual->nMulheresAtrasadas--;
		//sync_cout << "m u" << sync_endl;
		banheiroAtual->semMulher.unlock();
		Logger::log(0,SEM_M);
	}
	else{
	//	sync_cout << "e u" << sync_endl;
		banheiroAtual->e.unlock();
		Logger::log(0,SEM_E);
	}
}

Mulher::Mulher(int id) : Pessoa(id){}
