// Name: Luis Villalta
// Date: 1/23/24
// Title: Lab 2: Step 7
// Description: This program writes to the command line using the child process and exits using the parent. 

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(){
    pid_t pid;
    printf("\nBefore forking.\n");
    pid = fork();
    if(pid == -1)
        fprintf(stderr, "can't fork, error %d\n", errno);
    else if(pid == 0)
        execlp("/bin/ls", "ls", NULL);
    else{
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
    return 0;
}
