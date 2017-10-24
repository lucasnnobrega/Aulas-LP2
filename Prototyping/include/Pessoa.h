
#ifndef PESSOA_
#define PESSOA_
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <random>
#include "sync_printer.h"
#include "./Banheiro.h"

#define MIN_TIME 1000
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

        Banheiro* banheiroAtual = nullptr;

		int getId();
        virtual void entrarNoBanheiro(Banheiro* banheiro);
        void run();
        void necessidades();
        virtual void sairDoBanheiro();
        void dormir();
        Pessoa(int n, Banheiro* banheiroInicial);
		~Pessoa();
};
#endif
