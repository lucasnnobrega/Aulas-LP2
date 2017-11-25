#ifndef PESSOA
#define PESSOA 

#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>


class Pessoa(){

public:
    //Atributos
    int id;

    //Métodos
    void cortarCabelo();
};
#endif //PESSOA