#include "../include/Estabelecimento.h"

void Estabelecimento::addPessoa(int sex, int id){
    if(sexo == HOMEM){
        Pessoa *newPessoa = new Homem(id);
        pessoas.push_back(newPessoa);
    }else{
        Pessoa *newPessoa = new Mulher(id);
        pessoas.push_back(newPessoa);
    }
}

void Estabelecimento::iniciar(){
    
}

void Estabelecimento::set_nHomensAtrasados(int num){

}

void Estabelecimento::set_nMulheresAtrasadas(int num){

}

int Estabelecimento::get_nHomensAtrasados(){return nHomensAtrasados;}
int Estabelecimento::get_nMulheresAtrasadas(){return nMulheresAtrasadas;}

