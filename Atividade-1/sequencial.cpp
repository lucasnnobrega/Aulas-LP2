#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main ()
{
    //Tempo
    long T1;
    long T2;
    float tempo;

    T1 = clock();
    //Declarando matrizes
    int mt_linha = 4;
    int mt_coluna = 4;
    int mt1 [4][4] = {{1,2,3,4},{4,3,2,1},{2,2,2,2},{2,2,2,2}};
    int mt2 [4][4] = {{3,3,3,3},{3,3,3,3},{3,3,3,3},{3,3,3,3}};

    cout << "Matriz Resultante" << endl;
    int mtRES[4][4];

    //Zera a matriz resultado
    for (int i = 0; i < mt_linha; i++)
    for (int j = 0; j < mt_coluna; j++)
    mtRES[i][j] = 0;

    //Multiplicação
    for(int i = 0; i < mt_linha; i++)
        for(int j = 0; j < mt_coluna; j++)
            for(int k = 0; k < mt_linha; k++)
                mtRES[i][j] += mt1[i][k]*mt2[k][j];

    //Exibindo resultados
    for(int linha=0; linha < mt_linha; linha++)
    {
        for(int coluna=0;coluna < mt_coluna;coluna++)
        cout << mtRES[linha][coluna] << " ";
        cout << endl;
    }
    cout << endl;
    T2 = clock();
    tempo = (float)(T2-T1)/CLOCKS_PER_SEC;
    cout.precision(9);
    cout << "TEMPO = " << fixed << tempo << endl;
    return 0;
};