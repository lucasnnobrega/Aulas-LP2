#include "../include/Mulher.h"

int Mulher::entrarNoBanheiro(Banheiro *b){
	banheiroAtual = b;

	Logger::log(BLOQUEOU_SEM, SEM_E);
	b->e.lock();
	//Protocolo de entrada da seção critica
	//Mulher espera sempre que:
	if((b->capacidadeTotal == b->numeroDeMulheres) 
			|| (b->numeroDeHomens > 0)
			|| (b->mulheresConsecutivas == b->maxConsecutivos)
			||	 (b->nUtilizacoes + 1 >= b->maxUtilizacao))
			{
	
				b->nMulheresAtrasadas++;

				Logger::log(ENTROU_NA_FILA, id);
				sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou na fila \n" << b->toString() <<  sync_endl;
				
				Logger::log(LIBEROU_SEM, SEM_E);
				b->e.unlock();

				Logger::log(BLOQUEOU_SEM, SEM_M);
				b->semMulher.lock();

				if(b->nUtilizacoes >= b->maxUtilizacao){
					return 0;				
				}
	}
			
	//Após a entrada no banheiro, imediatamente
	b->nUtilizacoes++;
    b->numeroDeMulheres++;
	b->mulheresConsecutivas++;
	b->homensConsecutivos = 0;

	Logger::log(ENTROU_NO_BANHEIRO, id);
	sync_cout << id << " \033[1;35m[MULHER]\033[0m Entrou no banheiro \n" << b->toString() <<  sync_endl;
    
    //SIGNAL 1
    if(b->nMulheresAtrasadas > 0 && 
	   b->mulheresConsecutivas < b->maxConsecutivos &&
	   b->numeroDeMulheres < b->capacidadeTotal &&
	   b->nUtilizacoes + 1 <= b->maxUtilizacao
	   )
    {
		b->nMulheresAtrasadas--;

		Logger::log(LIBEROU_SEM, SEM_M);
		b->semMulher.unlock();
    }else{
		Logger::log(LIBEROU_SEM, SEM_E);
        b->e.unlock();
    }

	return 0;
}

void Mulher::sairDoBanheiro(){
	//Mulher sinaliza
	Logger::log(BLOQUEOU_SEM, SEM_E);
	banheiroAtual->e.lock();

	banheiroAtual->numeroDeMulheres--;

	Logger::log(SAIU_DO_BANHEIRO, id);
	sync_cout << id << " \033[1;35m[MULHER]\033[0m Saiu do banheiro \n" << banheiroAtual->toString() <<  sync_endl;

	if(banheiroAtual->numeroDeMulheres == 0 && banheiroAtual->nUtilizacoes + 1 > banheiroAtual->maxUtilizacao){
		Logger::end();
		std::exit(0);
	}

	//SIGNAL 2
	if(banheiroAtual->nHomensAtrasados > 0 && 
		banheiroAtual->numeroDeMulheres == 0 && 
		(banheiroAtual->nUtilizacoes <= banheiroAtual->maxUtilizacao))
	{
		banheiroAtual->nHomensAtrasados--;

		Logger::log(LIBEROU_SEM, SEM_H);
		banheiroAtual->semHomem.unlock();

	}else if(banheiroAtual->nMulheresAtrasadas > 0 && 
		banheiroAtual->mulheresConsecutivas < banheiroAtual->maxConsecutivos && 
		banheiroAtual->nUtilizacoes + 1<= banheiroAtual->maxUtilizacao
		){
		
		banheiroAtual->nMulheresAtrasadas--;

		Logger::log(LIBEROU_SEM, SEM_M);
		banheiroAtual->semMulher.unlock();
	}
	else{
		Logger::log(LIBEROU_SEM, SEM_E);
		banheiroAtual->e.unlock();
	}
}

Mulher::Mulher(int id) : Pessoa(id){}
