// Name: Luis Villalta
// Date: 1/23/24
// Title: Lab 2: Step 6
// Description: Simalar to step 1, but with the use of threads instead of processes

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

void thread(int n){
    int i;
    printf("%d", n);
    for(i=0;i<100;i++){
        printf("Child process %d\n", i);
        usleep(n);
    }
}

int main(int argc, char *argv[]){
    pthread_t thread_id;
    int i, n = atoi(argv[1]);
    printf("\nBefore threading.\n");
    int code = pthread_create(&thread_id, NULL, &thread, n); 

    for(i=0;i<100;i++){
            printf("\t \t \t Parent Process %d \n", i); 
            usleep(n); 
        }

    pthread_join(thread_id, NULL); 
    return 0;
}

