// Name: Luis Villalta
// Date: 2/17/24
// Title: Lab 5 Synchronization Using Semaphores
// Description: This program uses semphores to synchronizes threads, where 5 threads are producers that fill up a 
//              buffer until its full, then posts "full" so the consumer knows to begin to remove items from the
//              buffer until  its empty, then posts "empty" so the producer knows to begin to add items.              

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>
#include <stdlib.h>

pthread_t threads[10];
sem_t *mutex, *full, *empty;
int buffer[10], fu = 0, emp = 0;

void *producer(void *t){
    int item;
    do{
        sleep(1);
        item = rand() % 10;
        sem_wait(empty);
        sem_wait(mutex);
        buffer[fu] = item;
        fu = (fu + 1) % 10;
        printf("Item added was %d \n", item);
        sem_post(mutex);
        sem_post(full);
    } while(1);
}

void *consumer(void *t){
    int item;
    do{
        sem_wait(full);
        sem_wait(mutex);
        item = buffer[emp];
        //buffer[emp] = 0;
        emp = (emp + 1) % 10;
        printf("Item removed was %d \n", item);
        sem_post(mutex);
        sem_post(empty);
    } while(1);
}

int main(){
    pthread_t threads[10];
    int i;
    sem_unlink("mutex"); 
    sem_unlink("full"); 
    sem_unlink("empty"); 

    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    full = sem_open("full", O_CREAT, 0644, 0);
    empty = sem_open("empty", O_CREAT, 0644, 5);
    srand(time(NULL));

    //producer threads
    for(i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, producer, (void*)(intptr_t)i); 
    //consumer threads
    for(i = 5; i < 10; i++)
        pthread_create(&threads[i], NULL, consumer, (void*)(intptr_t)i); 
    
    for (i = 0; i < 10; i++) 
        pthread_join(threads[i],NULL); 
    
    sem_unlink("mutex"); 
    sem_unlink("full"); 
    sem_unlink("empty"); 
    return 0; 
}