#include <stdio.h>
#include <omp.h>

#define N 10000

int main() {
    int sum = 0;
    int vector[N];

    // Inicializar el vector con valores de ejemplo
    for (int i = 0; i < N; i++) {
        vector[i] = i;
    }

    // Habilitar el trabajo paralelo
    #pragma omp parallel num_threads(4)
    {
        int local_sum = 0;
        int tid = omp_get_thread_num();
        int chunk_size = N / omp_get_num_threads();

        // Sumar los elementos del vector en paralelo
        #pragma omp for schedule(static, chunk_size)
        for (int i = 0; i < N; i++) {
            local_sum += vector[i];
        }

        // Agregar el resultado parcial al total
        #pragma omp critical
        {
            sum += local_sum;
        }

        printf("Hilo %d suma local: %d\n", tid, local_sum);
    }

    printf("La suma del vector es: %d\n", sum);

    return 0;
}
