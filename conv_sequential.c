#include<stdio.h>
#include<stdlib.h>

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
    int *ANS = malloc(sizeof(int) * NANS);

    for (int i = 0; i < NANS; i++) {
      int temp = 0;
      for (int j = 0; j < NF; j++ ) {
        temp += A[i + j] * F[NF - j - 1];
      }
      ANS[i] = temp;
    }

    for (int i = 0; i < NANS; i++) {
        printf("%d\n", ANS[i]);
    }
    free(ANS);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}

