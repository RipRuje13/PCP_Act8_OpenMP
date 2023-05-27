#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100

// Función para encontrar el mínimo y máximo de un subvector
void find_min_max(int* subvec, int* min, int* max) {
    *min = subvec[0];
    *max = subvec[0];
    for (int i = 1; i < N/4; i++) {
        if (subvec[i] < *min) {
            *min = subvec[i];
        }
        if (subvec[i] > *max) {
            *max = subvec[i];
        }
    }
}

int main() {
    int vec[N];
    int subvecs[4][N/4];
    int mins[4], maxs[4];
    int min_val, max_val;

    // Inicializar el vector de 10000 elementos con enteros aleatorios entre 0 y 999
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        vec[i] = rand() % 1000;
    }

    // Dividir el vector en cuatro subvectores de igual tamaño
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < N/4; j++) {
            subvecs[i][j] = vec[i*N/4 + j];
        }
    }

    // Procesar cada subvector en un hilo diferente
    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        find_min_max(subvecs[tid], &mins[tid], &maxs[tid]);
    }

    // Obtener el mínimo y máximo del vector completo combinando los resultados
    min_val = mins[0];
    max_val = maxs[0];
    for (int i = 1; i < 4; i++) {
        if (mins[i] < min_val) {
            min_val = mins[i];
        }
        if (maxs[i] > max_val) {
            max_val = maxs[i];
        }
    }

    // Imprimir el mínimo y máximo del vector completo
    printf("Mínimo: %d\n", min_val);
    printf("Máximo: %d\n", max_val);

    // Imprimir los subvectores que maneja cada hilo
    for (int i = 0; i < 4; i++) {
        printf("\n");
        printf("Hilo %d maneja: \n[ ", i+1);
        for (int j = 0; j < N/4; j++) {
            printf("%d ", subvecs[i][j]);
        }
        printf("]\n");
    }

    return 0;
}
