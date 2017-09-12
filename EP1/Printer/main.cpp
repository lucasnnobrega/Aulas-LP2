#include <iostream>
#include <thread>
#include "./include/Printer.h"

using namespace std;
/*
void function(){

    string frases[] = {"Assim que acabar a corrida a gente testa", \ 
            "Agora está sendo recalculado , um negócio aleatório",
            "Entrou lá os 3 primeiros"}

}
*/


int main(){

    std::cout<<"teste de string"<<endl;
    Printer printer;
    
        thread firstThread([&printer](){
            while(1)
                printer.exec();
    
        });
        thread secondThread([&printer](){
            while(1)
                printer.exec();
        });
    
        firstThread.join();
        secondThread.join(); 

}