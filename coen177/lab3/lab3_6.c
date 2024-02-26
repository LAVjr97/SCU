// Name: Luis Villalta
// Date: 2/3/24
// Title: Lab 3: Step 6
// Description: Creates a two processes to handle a system call " cat /etc/passwd" and passing it through a pipe to
//              the other process that handles another system call "grep root" 
//              handles the response and formats it with spaces in between each character. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10
pthread_t threads[NTHREADS];
int main() {
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, &i);
    for (i = 0; i < NTHREADS; i++) {
	printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done.\n");
    return 0;
}
void *go(void *arg) {
 printf("Hello from thread %d with iteration %d\n",  (int)pthread_self(), *(int *)arg);
 return 0;
}


