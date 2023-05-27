#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define n 10

int main()
{
    clock_t t_ini, t_fin;
    double secs;
    t_ini = clock();

    int k, i, j;

    //Ingreso de la primera matriz
    double *M = (double*) malloc(n * n * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            M[i*n+j] = (0.1 + (j+i))/10;

    //Ingreso de la segunda matriz
    double *M1 = (double*) malloc(n * n * sizeof(double));
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            M1[i*n+j] = (0.1 + (0.20*j + 0.10*i))/10;

    //Producto de las matrices
    double *R = (double*) malloc(n * n * sizeof(double));
#pragma omp parallel for private(k,j) schedule(static,4)
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                R[k*n+i] += M[k*n+j] * M1[j*n+i];

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.2f\t", R[i*n+j]);
        }
        printf("\n");
    }

    // Fin paralelismo
    t_fin = clock();
    secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;

    printf("\n%.16g segundos producto A*B\n", secs);

    getchar(); // Espera a que se presione una tecla antes de salir
    return 0;
}
