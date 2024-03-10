#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <pthread.h>

typedef struct
{
    char
}info;


void *go(void *);


int main(int argc, char *argv[]){
    char buffer[atoi(argv[2])];
    int i, NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];

    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);
    
    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);

    return 0;
}

void *go(void *arg){
    FILE *fp, *rp;
    fp = fopen(argv[1], "rb");
    rp = fopen("step4Results.txt", "wb");
    
    while (fread(buffer, sizeof(buffer), 1, fp))
        fwrite(buffer, sizeof(buffer), 1, fp);
    
    fclose(fp);
    fclose(rp);
    return 0;
}

