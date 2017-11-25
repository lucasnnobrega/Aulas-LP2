#ifndef CLIENTE
#define CLIENTE

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "./include/Pessoa.h"

class Cliente : public Pessoa{
    
public:
    //Métodos
    void entrarBarbearia();

    void esperarCadeira();
    
    void cortarCabelo();
    
    void sairBarbearia();


};
#endif //PESSOA