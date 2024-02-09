//Shared data: semaphore full, empty, mutex;
//pool of n buffers, each can hold one item
//mutex provides mutual exclusion to the buffer pool
//empty and full count the number of empty and full buffers
//Initially: full = 0, empty = n, mutex = 1
//Producer thread
do {
...
produce next item
...
wait(empty);
wait(mutex);
...
add the item to buffer
...
signal(mutex);
signal(full);
} while (1);
//Consumer thread
do {
wait(full)
wait(mutex);
...
remove next item from buffer
...
signal(mutex);
signal(empty);
...
consume the item
...
} while (1);

////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h>


pthread_t threads[2];
sem_t *mutex;
char buffer[50];

void producer(){
    int i;
    char buff[50];

    do{
        printf("Give something to the producer \n");
        scanf("%s", buff);
        //wait empty
        //wait mutex

        for(i = 0; i < 10; i++);
            buffer[i] = i;
        //signal(mutex)
        //signal(full)
    } while(1);
}

void consumer(){
    do{
        //wait full
        //wait mutex

        //remove next item

        //signal(mutex)
        //signal(empty)
        

    } while(1);
}

int main(){
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    
    //producer
    pthread_create(&threads[0], NULL, producer, (void *)(size_t)i);
    //consumer
    pthread_create(&threads[1], NULL, consumer, (void *)(size_t)i);
    
    for (i = 0; i < 2; i++) {
        pthread_join(threads[i],NULL);
    }
    sem_unlink("mutex"); 
    return 0;
}