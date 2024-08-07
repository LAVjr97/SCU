// Name: Luis Villalta
// Date: 1/23/24
// Title: Lab 2: Step 1
// Description: Creates parent and child processes and haves them run simultaneously 



#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]){
    pid_t pid;
    int i, n = atoi(argv[1]); 
    printf("\n Before forking.\n"); 
    pid = fork();
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
