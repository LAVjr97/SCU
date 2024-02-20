// Name: Luis Villalta
// Date: 2/17/24
// Title: Lab 5 Synchronization Using Mutex Locks
// Description: This program uses mutex locks to synchronize its threads. 
            
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t lock; 

void* go(void* arg) { 
  pthread_mutex_lock(&lock); //entry section
  printf("Thread %ld Entered Critical Section..\n", (long)arg); //critical section 
  sleep(1); 
  pthread_mutex_unlock(&lock); //exit section 
  return (NULL);
} 

int main() { 
pthread_mutex_init(&lock, NULL);
static int i;
for (i = 0; i < NTHREADS; i++)  
   pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
for (i = 0; i < NTHREADS; i++) {
   pthread_join(threads[i],NULL);
   printf("\t\t\tThread %d returned \n", i);
   }
printf("Main thread done.\n");
pthread_mutex_destroy(&lock); 
return 0; 
} 
