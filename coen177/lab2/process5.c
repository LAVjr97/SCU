#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]); 
    printf("\nBefore forking.\n");
    /*pid = fork();
    if(pid == -1)
        fprintf(stderr, "can't fork, error %d\n", errno);
    if(pid == 0){
        pid = fork();
        printf("Child process\n");
        usleep(n/2);
        /*for(i=0;i<2;i++){
            printf("Child process %d\n", i);
            usleep(n/2);
        }
    }
    else{
        pid = fork();
        printf("\t \t \t Parent Process\n");
        usleep(n/2);
        /*for(i=0;i<7;i++){
            printf("\t \t \t Parent Process %d \n", i);
            usleep(n);
        }
    }*/
    pid = fork();
    for(i = 0; i < 3; i++){
        if(pid == -1)
            fprintf(stderr, "can't fork, error %d\n", errno);
        if(pid == 0){
            printf("Child process %d\n", pid);
            exit(0);
        }
        else{
            printf("\t \t \t Parent Process %d\n", pid);
            pid = fork();
            wait();
        }
    }
    

    return 0;
}
