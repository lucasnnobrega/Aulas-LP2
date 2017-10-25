#include "../include/Estabelecimento.h"

int n_homem;
int n_mulher;
int max_utilizacao;
int capacidade_banheiro;
int utilizacao_consec;

int main(int argc, char* argv[]){

    //sync_cout<<"Utilização: ./main [NUMERO DE HOMENS] [NUMERO DE MULHERES] [MAXIMO DE UTILIZAÇÕES DO BANHEIRO] [CAPACIDADE DO BANHEIRO] [MAXIMO DE UTILIZAÇÕES CONSECUTIVAS]" << sync_endl;

    if(argc == 6){
        n_homem              = atoi(argv[1]);
        n_mulher             = atoi(argv[2]);
        max_utilizacao       = atoi(argv[3]);
        capacidade_banheiro  = atoi(argv[4]);
        utilizacao_consec    = atoi(argv[5]);
		
		sync_cout << "Variáveis atribuidas com sucesso" << sync_endl;
		
		sync_cout << "argv ->" << " n_homem             = " << n_homem             << sync_endl;
        sync_cout << "argv ->" << " n_mulher            = " << n_mulher            << sync_endl;
        sync_cout << "argv ->" << " max_utilizacao      = " << max_utilizacao      << sync_endl;
        sync_cout << "argv ->" << " capacidade_banheiro = " << capacidade_banheiro << sync_endl;
        sync_cout << "argv ->" << " utilizacao_consec   = " << utilizacao_consec   << sync_endl;
	
    }else{
        sync_cout << "Numero de argumentos errado.\nUtilização: ./main [NUMERO DE HOMENS] [NUMERO DE MULHERES] [MAXIMO DE UTILIZAÇÕES DO BANHEIRO] [CAPACIDADE DO BANHEIRO] [MAXIMO DE UTILIZAÇÕES CONSECUTIVAS]" << sync_endl;        
		std::exit(1);
	}

	//capacidade e máximos consecutivos
	Banheiro meuBanheiro(capacidade_banheiro, utilizacao_consec, max_utilizacao);
	sync_cout << "Banheiro criado" << sync_endl;
	Estabelecimento meuEstabelecimento;
	sync_cout << "Estabelecimento criado" << sync_endl;

	meuEstabelecimento.set_banheiro(&meuBanheiro);

//####################### Cria Homens com o ID impar e Mulheres com o ID par #############################
	int id_homem = 1;
	int id_mulher = 2;

	for(int i = 0; i < n_homem;i = i + 1){
		//sync_cout<<id_homem<<"h"<<sync_endl;
		meuEstabelecimento.addPessoa(HOMEM, id_homem, &meuBanheiro);
		id_homem = id_homem + 2;
	}
	for(int j = 0; j < n_mulher;j = j + 1){
		//sync_cout<<id_mulher<<"m"<<sync_endl;
		meuEstabelecimento.addPessoa(MULHER, id_mulher, &meuBanheiro);
		id_mulher = id_mulher + 2;
		
	}
//#######################################################################################################

	char a;
	std::cin >> a;

	meuEstabelecimento.iniciar();

}