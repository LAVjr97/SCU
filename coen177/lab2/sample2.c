#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]); 
    printf("\nBefore forking.\n");
    pid = fork();
    if(pid == -1)
        fprintf(stderr, "can't fork, error %d\n", errno);
    if(pid)
        for(i=0;i<7;i++){
            printf("\t \t \t Parent Process %d \n", i);
            usleep(n);
        }
    else   
        for(i=0;i<2;i++){
            printf("Child process %d\n", i);
            usleep(n);
        }
    return 0;
}