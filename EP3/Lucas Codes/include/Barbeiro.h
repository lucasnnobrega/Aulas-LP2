#ifndef BARBEIRO
#define BARBEIRO

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "./include/Pessoa.h"

class Barbeiro: public Pessoa{
    
public:
    //Métodos
    void liberarCadeira();

    void dormir();
    
    void liberarSaida());


};
#endif //PESSOA