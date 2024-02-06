#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define N 5
#define M 5
#define L 4

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];

void calculateMatrixC(int i){
    for (int j = 0; j < L; j++){
        double temp = 0;
        for (int k = 0; k < M; k++){
            temp += matrixA[i][k] * matrixB[k][j];
        }
        matrixC[i][j] = temp;
    }
}

int main(){
    pthread_t thread_id[N];

    int i, j;

    //initializes the values for matrix A & B
    srand(time(NULL));
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            matrixA[i][j] = rand();

    srand(time(NULL));
    for (i = 0; i < M; i++)
        for (j = 0; j < L; j++)
            matrixB[i][j] = rand();

    for(i = 0; i < N; i++){
        pthread_create(&thread_id[N], NULL, &calculateMatrixC, i);
    }

    for(i = 0; i < N; i++){
        pthread_join(thread_id[N], NULL);
    }

    for(i = 0; i < N; i++)
        for(j = 0; j < L; i++){
            if(j + 1 == L)
                printf("%f\n", matrixC[i][j]);
            else
                printf("%f ", matrixC[i][j]);
        }

}