#ifndef MULHER_
#define MULHER_
#include "Pessoa.h"

class Banheiro;

class Mulher : public Pessoa{
    public:
    void entrarNoBanheiro(Banheiro* banheiro);
    void sairDoBanheiro();
	Mulher(int id);
};

#endif
