/*  Name: Luis Villalta
    Date: 2/10/24
    Title: Lab 4 Matrix Multiplication Using Threads
    Description: This program does Matrix multiplication using threads. Specifically, every row in MatrixC is
                 assigned as a job to a thread. Which all the threads then join before printing out the rsulting 
                 matrix. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define N 4
#define M 3
#define L 2

double matrixA[N][M];
double matrixB[M][L];
double matrixC[N][L];


void *calculateMatrixC(void *t){
    double temp; 
    int i = (int)(intptr_t)t, j, k;

    printf("\nThread, %d, doing its work\n", i);
    for (j = 0; j < L; j++){
        temp = 0;
        for (k = 0; k < M; k++){
            temp += matrixA[i][k] * matrixB[k][j];
        }
        printf("%d, %d\n", j, i);
        matrixC[i][j] = temp;
    }
    return 0;
}

void printMatrix(int row, int col, double matrix[row][col]){
    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++)
                printf("%0.1f ", matrix[i][j]);
        printf("\n");
    }
    printf("\n\n");
    return;
}

int main(){
    pthread_t thread_id[N];
    static int i; 
    int j;

    //initializes the values for matrix A & B
    srand(time(NULL));
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            matrixA[i][j] = rand() % 10;
        
    for (i = 0; i < M; i++)
        for (j = 0; j < L; j++)
            matrixB[i][j] = rand() % 10; 


    for(i = 0; i < N; i++)
        pthread_create(&thread_id[i], NULL, calculateMatrixC, (void*)(intptr_t)i);
    

    for(i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    

    printf("All threads joined\n\n");
    printMatrix(N, M, matrixA);
    printMatrix(M, L, matrixB);
    printMatrix(N, L, matrixC);
}