
#ifndef PESSOA
#define PESSOA
#include <iostream>
#include <mutex>
#include <random>
#include "sync_printer.h"

#define MIN_TIME 1000
#define MAX_TIME 3000

using namespace std;

class Banheiro;

//GERANDO  VALORES ALEATORIOS QUE SERÃO UTILIZADOS NO SLEEP
class RandomGenerator{	
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    public:
        RandomGenerator(int min = MIN_TIME, int max = MAX_TIME) : dis(min,max){
            gen.seed(rd());
        }
        double operator()(){
            return dis(gen);
        }
};

class Pessoa{
    protected:
        RandomGenerator randomDis;
        Banheiro* banheiroAtual;
        int id;

    public:
        virtual void entrarNoBanheiro(Banheiro& banheiro);
        void necessidades();
        virtual void sairDoBanheiro();
        void dormir();
        Pessoa(int n){};
};
#endif
