
#include "../include/Banheiro.h"

bool Banheiro::cheio(){
	return (numeroDeMulheres + numeroDeHomens == capacidadeTotal) ? true : false;
}

Banheiro::Banheiro(int maxPessoas, int maxConsecutivos_) : capacidadeTotal(maxPessoas), maxConsecutivos(maxConsecutivos_){
	semMulher.lock();
}

//Getters
int Banheiro::get_capacidadeTotal     (){ return capacidadeTotal;    }
int Banheiro::get_maxConsecutivos     (){ return maxConsecutivos;    }
int Banheiro::get_numeroDeMulheres    (){ return numeroDeMulheres;   }
int Banheiro::get_numeroDeHomens      (){ return numeroDeHomens;     }
int Banheiro::get_nMesmoSexo          (){ return nMesmoSexo;         } 
int Banheiro::get_nMulheresAtrasadas  (){ return nMulheresAtrasadas; }
int Banheiro::get_nHomensAtrasados    (){ return nHomensAtrasados;   }



//Setters
void Banheiro::set_capacidadeTotal    (int a){ capacidadeTotal = a;    }
void Banheiro::set_maxConsecutivos    (int a){ maxConsecutivos = a;    }
void Banheiro::set_numeroDeMulheres   (int a){ numeroDeMulheres = a;   }
void Banheiro::set_numeroDeHomens     (int a){ numeroDeHomens = a;     }
void Banheiro::set_nMesmoSexo         (int a){ nMesmoSexo = a;         }
void Banheiro::set_nMulheresAtrasadas (int a){ nMulheresAtrasadas = a; }
void Banheiro::set_nHomensAtrasados   (int a){ nHomensAtrasados = a;   }  
