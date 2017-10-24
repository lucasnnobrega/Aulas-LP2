
#include "../include/Banheiro.h"

bool Banheiro::cheio(){
	return (numeroDeMulheres + numeroDeHomens == capacidadeTotal) ? true : false;
}

Banheiro::Banheiro(int maxPessoas, int maxConsecutivos_) : capacidadeTotal(maxPessoas), maxConsecutivos(maxConsecutivos_){
	semHomem.lock();
	semMulher.lock();
}

std::string Banheiro::toString(){
	std::stringstream stream;	
	stream << "(dH,dM,nH,nM,mC,hC) = \n(" << 
	nHomensAtrasados << "," << nMulheresAtrasadas << "," << numeroDeHomens << "," <<
	numeroDeMulheres << "," << mulheresConsecutivas << "," << homensConsecutivos << ")";
	return stream.str();
}

//Getters
int Banheiro::get_capacidadeTotal     (){ return capacidadeTotal;    }
int Banheiro::get_maxConsecutivos     (){ return maxConsecutivos;    }
int Banheiro::get_numeroDeMulheres    (){ return numeroDeMulheres;   }
int Banheiro::get_numeroDeHomens      (){ return numeroDeHomens;     }
int Banheiro::get_homensConsecutivos  (){ return homensConsecutivos; }
int Banheiro::get_mulheresConsecutivas  (){ return mulheresConsecutivas; }
int Banheiro::get_nMulheresAtrasadas  (){ return nMulheresAtrasadas; }
int Banheiro::get_nHomensAtrasados    (){ return nHomensAtrasados;   }



//Setters
void Banheiro::set_homensConsecutivos (int a){ homensConsecutivos = a; }
void Banheiro::set_capacidadeTotal    (int a){ capacidadeTotal = a;    }
void Banheiro::set_maxConsecutivos    (int a){ maxConsecutivos = a;    }
void Banheiro::set_numeroDeMulheres   (int a){ numeroDeMulheres = a;   }
void Banheiro::set_numeroDeHomens     (int a){ numeroDeHomens = a;     }
void Banheiro::set_nMulheresAtrasadas (int a){ nMulheresAtrasadas = a; }
void Banheiro::set_nHomensAtrasados   (int a){ nHomensAtrasados = a;   }  
void Banheiro::set_mulheresConsecutivas (int a){ mulheresConsecutivas = a; }
