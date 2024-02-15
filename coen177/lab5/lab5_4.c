//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1
//Producer thread 

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>
#include <stdlib.h>

pthread_t threads[10];
pthread_mutex_t mutex;
pthread_cond_t full, empty;
int buffer[10], fu = 0, emp = 0, buff = 0;

void *producer(void *t){
    int item;
    do{
        item = rand() % 10;
        pthread_mutex_lock(&mutex);
        while(buff == 10) 
            pthread_cond_wait(&empty, &mutex);
        buffer[fu] = item;
        fu = (fu + 1) % 10;
        buff++;
        printf("Item added was %d \n", item);
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    } while(1);
}

void *consumer(void *t){
    int item;
    do{
        pthread_mutex_lock(&mutex);
        while(buff == 0)
            pthread_cond_wait(&full, &mutex);
        item = buffer[emp];
        buffer[emp] = 0;
        emp = (emp + 1) % 10;
        buff--;
        printf("Item removed was %d \n", item);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    } while(1);
}

int main(){
    pthread_t threads[10];
    int i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_wait(&full, &mutex);
    pthread_cond_wait(&empty, &mutex);

    srand(time(NULL));
    //producer threads
    for(i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, producer, (void*)(intptr_t)i);

    //consumer threads
    for(i = 5; i < 10; i++)
        pthread_create(&threads[i], NULL, consumer, (void*)(intptr_t)i); 
    
    for (i = 0; i < 10; i++)
        pthread_join(threads[i],NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
}