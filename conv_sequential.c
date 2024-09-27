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
    int temp = 0;
    int *ANS = malloc(sizeof(int) * NA);
    for (int i = 0; i < NA; i++) {
        ANS[i] = 0;
        for (int j = 0; j < NF; j++) {
            if (i - j >= 0 && i - j < NA) {
                ANS[i] += A[i - j] * F[j];
            }
        }
    }
    for (int i = 0; i < NA; i++) {
        printf("%d\n", ANS[i]);
    }
    free(ANS);

    // ---- free memory ----
    free(F);
    free(A);
    // ---- end free ----
    return 0;
}

