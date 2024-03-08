#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

typedef struct {
    int pageno;
} ref_page;

int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0;
    int i, cache_i;
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    printf("Page Number that was not found: ");
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        totalRequests++;

        for (i=0; i < CACHE_SIZE - 1; i++)
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break; //break out loop because found page_num in cache
            }
        
        if (foundInCache == false){
            //You may print the page that caused the page fault
            cache[cache_i].pageno = page_num;
            totalFaults++
            cache_i = (cache_i + 1) % CACHE_SIZE; //Need to keep the value within the cacheSize
            printf("%d ", page_num);
        }
    }
    double hitRate = (totalRequests - totalFaults) / totalRequests;
    printf("\n%d Total Requests \n%d Total Page Faults \n%d Hit Rate", totalRequests, totalFaults, hitRate);
    return 0;
}

//Cache Size 50
//FIFO: 9595
//LRU: 9595
//