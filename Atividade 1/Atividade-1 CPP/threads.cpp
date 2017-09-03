#include <iostream>
#include <ctime>
#include <thread>

using namespace std;

//Declarando matrizes
int mt_linha = 4;
int mt_coluna = 4;
int mt1 [4][4] = {{1,2,3,4},{4,3,2,1},{2,2,2,2},{2,2,2,2}};
int mt2 [4][4] = {{3,3,3,3},{3,3,3,3},{3,3,3,3},{3,3,3,3}};

std::thread t[16];

int mtRESULT[4][4];

void intern(int linha_T, int col_T)
{
    int acc = 0;
    for(int i = 0; i < mt_coluna; i++) {
        acc += mt1[linha_T][i] * mt2[i][col_T];
    }
    mtRESULT [linha_T][col_T] = acc;
}

int main ()
{
    //Tempo
    long T1;
    long T2;
    float tempo;

    T1 = clock();

    cout << "Matriz Resultante" << endl;

    //Zera a matriz resultado
    for (int i = 0; i < mt_linha; i++)
        for (int j = 0; j < mt_coluna; j++)
            mtRESULT[i][j] = 0;
    int index = 0;
    //Multiplicação
    for(int i = 0; i < mt_linha; i++) {
        for (int j = 0; j < mt_coluna ; j++, index++)
                t[index] = std::thread(intern, i, j);
    }
    for(int i = 0; i < 16; i++){
        if(t[i].joinable())
            t[i].join();
    }
    // Exibindo resultados
    for(int linha=0; linha < mt_linha; linha++)
    {
        for(int coluna=0;coluna < mt_coluna;coluna++)
            cout << mtRESULT[linha][coluna] << " ";
        cout << endl;
    }
    cout << endl;
    T2 = clock();
    tempo = (float)(T2-T1)/CLOCKS_PER_SEC;
    cout.precision(9);
    cout << "TEMPO = " << fixed << tempo << endl;
    return 0;
};