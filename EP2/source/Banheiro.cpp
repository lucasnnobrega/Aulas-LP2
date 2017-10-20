#include "../include/Banheiro.h"

bool Banheiro::cheio(){
	return (numeroDeMulheres + numeroDeHomens == capacidadeTotal) ? true : false;
}
