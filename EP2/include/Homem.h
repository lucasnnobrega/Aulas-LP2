#ifndef HOMEM
#define HOMEM
#include "Pessoa.h"

class Homem : public Pessoa{
    public:
        void entrarNoBanheiro(Banheiro *b);
        void sairDoBanheiro(Banheiro *b);
};
#endif
