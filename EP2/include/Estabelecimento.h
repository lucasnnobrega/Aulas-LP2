#include <iostream>
<<<<<<< HEAD
#include "Pessoa.h"
#include "Banheiro.h"
#include <mutex>
#include <vector>

#define HOMEM 1
#define MULHER 2
=======
#include "Pessoa.h
#include "Banheiro.h"
>>>>>>> 82ead4af1d018d1d7fcc6875cce28f5a8d49854f

#define MAX_PESSOAS_BANHEIRO 5
#define MAX_PESSOAS_TOTAL 10

class Estabelecimento{
<<<<<<< HEAD
  Banheiro banheiro(MAX_PESSOAS_BANHEIRO);
	std::vector<Pessoa*> pessoas;
  int nMulheresAtrasadas;
  int nHomensAtrasados;
  std::mutex semHomem;
  std::mutex semMulher;
  std::mutex semBox;
  
  public:
  void addPessoa(int sex);
  void iniciar();

  void set_nHomensAtrasados(int num);
  void set_nMulheresAtrasadas(int num);
  
  int get_nHomensAtrasados();
  int get_nMulheresAtrasadas();
};
=======
    Banheiro banheiro(MAX_PESSOAS_BANHEIRO);
    Pessoas pessoas[MAX_PESSOAS_TOTAL];
      public:
        
  };
>>>>>>> 82ead4af1d018d1d7fcc6875cce28f5a8d49854f
