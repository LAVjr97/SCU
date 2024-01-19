#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]){
    //pid_t pid;
    int i, n = atoi(argv[1]); 
    printf("\nBefore forking.\n");
    pid_t pid, pid2, pid3, pid4;

    //creates a child process
    pid = fork();

    //the child process creates a grandchild process 
    if(pid == 0)
        pid2 = fork();

    //parent creates a secondary child process, first child creates a second grandchild process, and first grandchild process creates a greatgrand child process
    pid3 = fork();

    //first grandchild process creates a second Greatgrand child
    if(pid3 != 0 && pid2 == 0)
        pid4 = fork();

    if(pid4 == 0 || (pid3 == 0 && pid2 == 0))
        printf("Great grand child to parent process\n");
    if((pid2 == 0 && pid == 0 && pid != 0) || (pid3 == 0 && pid2 != 0))
        printf("Grandchildren to parent process\n");
    if((pid == 0 && pid2 != 0 && pid3 != 0) || (pid3 == 0 && pid != 0))
        printf("Children to parent process\n");
    if(pid != 0 && pid3 != 0)
        printf("Parent Process\n");
    
    return 0;
}
