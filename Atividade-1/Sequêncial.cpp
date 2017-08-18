/*
    Multiplicação de matrizes AxB=C
    Método Sequencial

*/
#include <iostream>

using namespace std;

int main(){

    float matriz_A[2][2] = {{1, 2},\
                            {3, 4}};

    float matriz_B[2][2] = {{1, 2},\
                            {3, 4}};

    float matriz_C[2][2] = {{0, 0},\
                            {0, 0}};

    /*
    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            //cout << matriz_A[i][j] << endl;
            matriz_C[i][j] = matriz_A[i][j]*matriz_B[i][j] + matriz_A[i][j] * matriz_B[j][i];
        }
    }
    */
    for (int i=0;i<1; i++) {
        for (int j=0; j<1; j++) {
            for (int k=0; k<1; k++) {
                matriz_C[i][j] = matriz_C[i][j] + (matriz_A[i][k] * matriz_B[k][j]); 
                cout << i << j <<"  "<< matriz_C[i][j] << endl;
        }
      }
    }

    for(int i = 0; i <= 1; i++){
        for(int j = 0; j <= 1; j++){
            //cout << matriz_A[i][j] << endl;
            matriz_C[i][j] = matriz_A[i][j]*matriz_B[i][j] + matriz_A[i][j] * matriz_B[j][i];
            cout << i << j <<"  "<< matriz_C[i][j] << endl;
        }
    }



    cout<<"nothig"<<endl;

}