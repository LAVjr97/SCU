// Name: Luis Villalta
// Date: 3/17/24
// Title: Lab 9 - Step 5
// Description: This program uses a given number of threads to write new files using a give buffer size, which 
//              it reads from a given file. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <pthread.h>

typedef struct{
    char **args;
}info;

void *go(void *);

int main(int argc, char *argv[]){
    int i, NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];

    //initialize struct
    info arg;
    arg.args = argv;

    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, &arg);

    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);

    return 0;
}

void *go(void *arg){
    info* threadarg = (info *)arg;
    int buffSize = atoi((*threadarg).args[2]), nThread = atoi((*threadarg).args[3]);
    char buffer[buffSize];
    char *fname = (*threadarg).args[1];

    char newF[30];
    sprintf(newF, "%d_%d_%s", buffSize, nThread, fname);

    FILE *fp, *rp;
    fp = fopen(fname, "rb");
    rp = fopen(newF, "wb");

    while (fread(buffer, sizeof(buffer), 1, fp))
        fwrite(buffer, sizeof(buffer), 1, rp);
    
    fclose(fp);
    fclose(rp);
    return 0;

}

