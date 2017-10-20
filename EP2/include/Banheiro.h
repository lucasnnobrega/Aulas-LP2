#ifndef BANHEIRO
#define BANHEIRO
#include <iostream>
#include <mutex>

#include "../include/Homem.h"
#include "../include/Mulher.h"


class Banheiro{
    int max_pessoas;
    bool cheio = false;
    bool vazio = true;
       public: 
        Banheiro(int max_pessoas);
        bool banheiroCheio();
          bool banheiroVazio();
  };
#endif
