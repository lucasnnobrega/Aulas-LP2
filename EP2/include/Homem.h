#ifndef HOMEM__
#define HOMEM__
#include "Pessoa.h"
#include "sync_printer.h"

class Banheiro;

class Homem : public Pessoa {
    public:
        void entrarNoBanheiro(Banheiro *b);
        void sairDoBanheiro();
		Homem();
		Homem(int);
};
#endif
