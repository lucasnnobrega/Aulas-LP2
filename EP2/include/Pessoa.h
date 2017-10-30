
#ifndef PESSOA_
#define PESSOA_
#include <iostream>
#include <mutex>
#include <thread>
#include <random>
#include "Logger.h"
#include "sync_printer.h"
#include "./Banheiro.h"

#define ENTROU_NO_BANHEIRO 1
#define SAIU_DO_BANHEIRO 0
#define ENTROU_NA_FILA 2
#define CHEGOU_NO_ESTABELECIMENTO 5
#define LIBEROU_SEM 4
#define BLOQUEOU_SEM 3

#define SEM_H 6
#define SEM_M 8
#define SEM_E 7

#define MIN_TIME 1300
#define MAX_TIME 3000

using namespace std;


//GERANDO  VALORES ALEATORIOS QUE SERÃO UTILIZADOS NO SLEEP
class RandomGenerator{	
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    public:
        RandomGenerator(int min = MIN_TIME, int max = MAX_TIME) : dis(min,max){
            gen.seed(rd());
        }
        int operator()(){
            return dis(gen);
        }
};

class Pessoa{
    protected:
        RandomGenerator randomDis;
        std::thread *thread;
        int id;
    public:
		static bool barreira;

        Banheiro* banheiroAtual;

		int getId();
        virtual int entrarNoBanheiro(Banheiro* banheiro);
        void run();
        virtual void sairDoBanheiro();
        void dormir();
        Pessoa(int n);
		~Pessoa();
};
#endif
