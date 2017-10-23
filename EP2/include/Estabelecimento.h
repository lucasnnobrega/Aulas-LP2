#include <iostream>
#include <mutex>
#include <vector>
#include "./Homem.h"
#include "./Banheiro.h"
#include "./Mulher.h"
#include "./sync_printer.h"

#define HOMEM 1
#define MULHER 2

#define MAX_PESSOAS_BANHEIRO 5
#define MAX_PESSOAS_TOTAL 10

class Estabelecimento{
  bool start = 0;
  Banheiro *banheiro;
  std::vector<Pessoa*> pessoas;
  
  public:
  Estabelecimento(){}
  ~Estabelecimento();
  void set_banheiro(Banheiro* b);
  void addPessoa(int sex, int id, Banheiro* banheiroInicial);
  void iniciar();
};
