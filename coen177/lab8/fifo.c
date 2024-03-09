#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <stdbool.h>

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0;
    int i, cache_i=0;
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    //printf("Page Number that was not found: ");
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        totalRequests++;

        for (i=0; i < CACHE_SIZE; i++)
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break; //break out loop because found page_num in cache
            }
        
        if (foundInCache == false){
            printf("%d\n", page_num);
            //You may print the page that caused the page fault
            cache[cache_i].pageno = page_num;
            totalFaults++;
            
            cache_i = (cache_i + 1) % CACHE_SIZE; //Need to keep the value within the cacheSize
        }
    }

    double missRate = totalFaults / (double)totalRequests;
    double hitRate = 1 - missRate;
    printf("\n%d Total Requests \n%d Total Page Faults \n%0.3f Miss Rate \n%0.3f Hit Rate\n", totalRequests, totalFaults, missRate, hitRate);
    return 0;
}

//Cache Size 50 
//FIFO: 9595
//LRU: 9595