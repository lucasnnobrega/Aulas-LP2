#ifndef MULHER
#define MULHER
#include "Pessoa.h"

class Mulher : public Pessoa{
    public:
    void entrarNoBanheiro(Banheiro& banheiro);
        void sairDoBanheiro();
    };

#endif
