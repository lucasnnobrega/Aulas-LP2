#include <iostream>
#include <mutex>
#include <random>

#define MIN_TIME 1000
#define MAX_TIME 3000

using namespace std;

//GERANDO  VALORES ALEATORIOS QUE SERÃO UTILIZADOS NO SLEEP
struct randomGenerator{	
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
        public:
        randomGenerator(int min, int max) : dis(min,max){
        gen.seed(rd());
        }
        double operator()(){
            return dis(gen);
        }
};

class Pessoa{
        RandomGenerator randomDis(MIN_TIME, MAX_TIME);
        Banheiro* banheiroAtual;
          public:
            virtual void entrarNoBanheiro(Banheiro& banheiro);
            void sairDoBanheiro();
            void dormir();
        Pessoa(){};
};
