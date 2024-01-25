#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


int main(int argc, char *argv[]){
    pthread_t thread_id;
    int i, n = atoi(argv[1]); 
    printf("\nBefore threading.\n");
    int code = pthread_create(&thread_id, NULL, main, NULL); 
    pthread_join(thread_id, NULL); 
    if(code != 0)
        fprintf(stderr, "can't create thread, error %d\n", errno);
    if(code == 0)
        for(i=0;i<100;i++){
            printf("\t \t \t Parent Process %d \n", i);
            usleep(n);
        }
    else   
        for(i=0;i<100;i++){
            printf("Child process %d\n", i);
            usleep(n);
        }
    return 0;
}

//-lpthreads