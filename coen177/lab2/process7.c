
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
    else if(pid == 0)
        execlp("/bin/ls", "ls", NULL);
    else{
        wait(NULL);
        printf("Child Complete\n");
        exit(0);
    }
    return 0;
}
