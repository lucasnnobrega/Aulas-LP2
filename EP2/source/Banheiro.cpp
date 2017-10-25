
#include "../include/Banheiro.h"

bool Banheiro::cheio(){
	return (numeroDeMulheres + numeroDeHomens == capacidadeTotal) ? true : false;
}

Banheiro::Banheiro(int maxPessoas, int maxConsecutivos_, int maxUtilizacao) : capacidadeTotal(maxPessoas), maxConsecutivos(maxConsecutivos_), maxUtilizacao(maxUtilizacao){
	semMulher.lock();
	semHomem.lock();
}

std::string Banheiro::toString(){
	std::stringstream stream;	
	stream << "(dH,dM,nH,nM,mC,hC,mU,nU) = \n(" << 
	nHomensAtrasados << "," << nMulheresAtrasadas << "," << numeroDeHomens << "," <<
	numeroDeMulheres << "," << mulheresConsecutivas << "," << homensConsecutivos << ","<< 
	maxUtilizacao << "," << nUtilizacoes << ")";
	return stream.str();
}
