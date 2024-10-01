#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int NA, NF;
    
    // ---- input and malloc A, F ----
    scanf("%d %d", &NA, &NF);
    int *A = (int*)malloc(sizeof(int) * NA);
    int *F = (int*)malloc(sizeof(int) * NF);

    for (int i = 0; i < NA; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < NF; i++) {
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    int NANS = NA - NF + 1;
    int *ANS_seq = (int*)malloc(sizeof(int) * NANS);
    int *ANS_par = (int*)malloc(sizeof(int) * NANS);

    // Timing variables
    omp_set_num_threads(8);

    // ---- Timing for sequential convolution ----
    double start_seq = omp_get_wtime();
    for (int i = 0; i < NANS; i++) {
        int temp = 0;
        for (int j = 0; j < NF; j++) {
            temp += A[i + j] * F[NF - j - 1];
        }
        ANS_seq[i] = temp;
    }
    double end_seq = omp_get_wtime();

    // ---- Timing for parallel convolution ----
    double start_par = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < NANS; i++) {
            int temp = 0;
            for (int j = 0; j < NF; j++) {
                temp += A[i + j] * F[NF - j - 1];
            }
            ANS_par[i] = temp;
        }
    }
    double end_par = omp_get_wtime();

    // ---- Compare and Print Results ----
    printf("Sequential Convolution Result:\n");
    for (int i = 0; i < NANS; i++) {
        printf("%d ", ANS_seq[i]);
    }
    printf("\n");

    printf("Parallel Convolution Result:\n");
    for (int i = 0; i < NANS; i++) {
        printf("%d ", ANS_par[i]);
    }
    printf("\n");

    // ---- Time results ----
    double time_seq = end_seq - start_seq;
    double time_par = end_par - start_par;
    printf("Time taken by sequential convolution: %f seconds\n", time_seq);
    printf("Time taken by parallel convolution (4 threads): %f seconds\n", time_par);

    // Calculate and print speedup
    if (time_par > 0) {
        double speedup = time_seq / time_par;
        printf("Speedup achieved: %f times\n", speedup);
    } else {
        printf("Parallel execution time is zero, cannot calculate speedup.\n");
    }

    // ---- Free memory ----
    free(A);
    free(F);
    free(ANS_seq);
    free(ANS_par);
    // ---- end free ----

    return 0;
}
