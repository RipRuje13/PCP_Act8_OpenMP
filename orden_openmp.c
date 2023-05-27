#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000

int main()
{
    int a[N];

    // Inicializa el vector con valores aleatorios
    srand(0);
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        int start = id * N / 4;
        int end = (id + 1) * N / 4;
        for (int i = start; i < end; i++) {
            for (int j = i + 1; j < end; j++) {
                if (a[i] > a[j]) {
                    int temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                }
            }
        }
        printf("\nProcesador %d: ", id);
        for (int i = start; i < end; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }

    return 0;
}
