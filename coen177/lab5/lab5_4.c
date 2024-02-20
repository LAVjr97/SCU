// Name: Luis Villalta
// Date: 2/17/24
// Title: Lab 5 Synchronization Using Conditional Variables
// Description: This program uses conditional variables to properly synchronize the threads used as producers and consumers
//              The producer initially begins to fill the buffer until buffer is and it will have had the buffer counter
//              set to 10 and will also set the conditional signal to full. The consumer threads will then 
//              begin to remove items from the buffer until it is empty which will leave the buffer counter to 0. And will then
//              set the conditional variable to empty.

#include <stdio.h>    
#include <unistd.h>   
#include <pthread.h>  
#include <semaphore.h>
#include <stdlib.h>   

//pthread_t threads[10];
pthread_mutex_t mutex;
pthread_cond_t full, empty;
int buffer[10], fu = 0, emp = 0, buff = 0;

void *producer(void *t){
    int item;
    do{
        sleep(1); 
        item = rand() % 10;
        pthread_mutex_lock(&mutex);
        while(buff == 10) 
            pthread_cond_wait(&empty, &mutex);
        buffer[fu] = item;
        fu = (fu + 1) % 10;
        buff++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        printf("Item added was %d \n", item);
    } while(1);
}

void *consumer(void *t){
    int item;
    do{
        sleep(1);
        pthread_mutex_lock(&mutex);
        while(buff == 0)
            pthread_cond_wait(&full, &mutex);
        item = buffer[emp];
        buffer[emp] = 0;
        emp = (emp + 1) % 10;
        buff--;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        printf("Item removed was %d \n", item);

    } while(1);
}

int main(){
    pthread_t threads[10];
    int i, j;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    srand(time(NULL));
    //producer threads
    for(i = 0; i < 5; i++)
        pthread_create(&threads[i], NULL, producer, (void*)(intptr_t)i);

    //consumer threads
    for(j = 5; j < 10; j++)
        pthread_create(&threads[j], NULL, consumer, (void*)(intptr_t)j); 
    
    for (i = 0; i < 10; i++)
        pthread_join(threads[i],NULL);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
    return 0;
} 
