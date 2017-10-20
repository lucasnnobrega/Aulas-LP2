#include <iostream>
#include "Pessoa.h"
#include "Banheiro.h"
#include <mutex>
#include <vector>

#define HOMEM 1
#define MULHER 2

#define MAX_PESSOAS_BANHEIRO 5
#define MAX_PESSOAS_TOTAL 10

class Pessoa;

class Estabelecimento{
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
