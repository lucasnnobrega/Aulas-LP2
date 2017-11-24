#ifndef CLIENTE
#define CLIENTE

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include 


class Cliente(Pessoa){
    
public:
    //Métodos
    void entrarBarbearia();

    void esperarCadeira();
    
    void cortarCabelo();
    
    void sairBarbearia();


};
#endif //PESSOA