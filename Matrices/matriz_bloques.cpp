#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BlockSize 100
using namespace std;

int min(int a, int b)
{
    if(a < b) return a;
    return b;
}
void imprimir(int **a,int f,int c)
{
    for(int i=0;i<f;i++)
    {
        for(int j=0;j<c;j++)
        {
            cout<<a[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main()
{
    int **pm;
    int cols;
    int rows;

    cout << "Ingresa nro de filas: ";
    cin >> rows;

    cout << endl;
    cout << "Ingresa nro de columnas: ";
    cin >> cols;

    pm = new int* [rows];
    for (int i = 0; i < rows; i++) {
        pm[i] = new int[cols];
    }

    srand(time(NULL));
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            pm[i][j]= 1+rand()%(10-1);
            //cout<<pm[i][j]<<"\t";
        }
        //cout << endl;
    }
    cout << endl;
    //imprimir(pm,cols,rows);
    cout<<endl;
    int **b;
    int **c;
    b = new int* [rows];
    for (int i = 0; i < rows; i++) {
        b[i] = new int[cols];
    }
    //cout<<"Matriz B"<<endl;
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            b[i][j]= 1+rand()%(10-1);
            //cout<<b[i][j]<<"\t";
        }
        //cout << endl;
    }

    c = new int* [rows];
    for (int i = 0; i < rows; i++) {
        c[i] = new int[cols];
    }
    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {

            c[i][j]=0;
            //cout<<b[i][j]<<"\t";
        }
        //cout << endl;
    }
    cout << endl;
    cout<<"Multiplicacion"<<endl;

    unsigned t0,t1;
    t0 = clock();
    int jump=10;
    for(int ii = 0; ii < rows; ii+=jump)
        {
            for(int jj = 0; jj < rows; jj += jump)
            {
                for(int kk = 0; kk < rows; kk += jump)
                {
                    for(int i = ii; i < min(ii+jump,rows); i++)
                    {
                        for(int j = jj; j < min(jj+jump,rows); j++)
                        {
                            for(int k = kk; k < min(kk+jump,rows); k++)
                            {
                                c[i][j] += pm[i][k] * b[k][j];
                            }

                        }
                    }
                }
            }
        }


    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    //imprimir(c,cols,rows);
    return 0;

}
