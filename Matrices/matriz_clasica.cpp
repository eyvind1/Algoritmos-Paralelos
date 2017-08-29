#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <stdlib.h>
using namespace std;

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
    cout<<"Matriz B"<<endl;
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
    cout << endl;
    cout<<"Multiplicacion"<<endl;

    unsigned t0,t1;
    t0 = clock();
    for (int i=0;i<rows;i++)
    {for (int j=0;j<cols;j++)
       { c[i][j]=0;
         for (int k=0;k<cols;k++)
          {c[i][j]=c[i][j]+pm[i][k]*b[k][j];
          }
       }
    }
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    //imprimir(c,cols,rows);
    return 0;
}
