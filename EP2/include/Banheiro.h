#include <iostream>
#include <mutex>

class Banheiro{
    int max_pessoas;
    bool cheio = false;
    bool vazio = true;
       public: 
        Banheiro(int max_pessoas);
        bool banheiroCheio();
          bool banheiroVazio();
  };