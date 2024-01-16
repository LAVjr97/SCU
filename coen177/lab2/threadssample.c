#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


int main(int argc, char *argv[]){
    int pthread_create(pthread_t *thread, pthread_attr_t *attr, void*(*start_routine) (void *arg), void *arg);
    pthread_t thread_id;
    int i, n = atoi(argv[1]); 
    printf("\n Before threading.\n");
    pid = pthread_create(thread_id, NULL, main, );
    if(pid == -1)
        fprintf(stderr, "can't fork, error %d\n", errno);
    if(pid)
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
