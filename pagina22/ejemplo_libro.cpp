#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define MAX 480
int main()
{
    unsigned t0,t1;
    double A[MAX][MAX], x[MAX], y[MAX];
    t0 = clock();
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            y[i] += A[i][j]*x[j];
        }
    }
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;

    /*t0 = clock();
    for (int j = 0; j < MAX; j++)
    {
        for (int i = 0; i < MAX; i++)
        {
            y[i] += A[i][j]*x[j];
        }
    }
    t1=clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;*/
    return 0;
}

