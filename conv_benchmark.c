#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(){
    // ---- input and malloc A, F ----
    int NA, NF;
    scanf("%d %d", &NA, &NF);
    int *A = malloc(sizeof(int) * NA);
    int *F = malloc(sizeof(int) * NF);

    for(int i = 0; i < NA; i++){
        scanf("%d", &A[i]);
    }
    for(int i = 0; i < NF; i++){
        scanf("%d", &F[i]);
    }
    // ---- end input and malloc----

    // implement here

    int NANS = NA - NF + 1;
    int *ANS_seq = malloc(sizeof(int) * NANS);
    int *ANS_par = malloc(sizeof(int) * NANS);

    double start_seq = omp_get_wtime();
    
    for (int i = 0; i < NANS; i++) {
      int temp = 0;
      for (int j = 0; j < NF; j++ ) {
        temp += A[i + j] * F[NF - j - 1];
      }
      ANS_seq[i] = temp;
    }

    double end_seq = omp_get_wtime();
    double seq_time = end_seq - start_seq;
    printf("Serial execution time: %f seconds\n", seq_time);

    double start_par = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < NANS; i++) {
      int temp = 0;
      for (int j = 0; j < NF; j++ ) {
        temp += A[i + j] * F[NF - j - 1];
      }
      ANS_par[i] = temp;
    }

    double end_par = omp_get_wtime();
    double par_time = end_par - start_par;
    printf("Parallel execution time: %f seconds\n", par_time);

    double speedup = seq_time / par_time;
    printf("Speed up: %f\n", speedup);

    free(ANS_seq);
    free(ANS_par);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}

