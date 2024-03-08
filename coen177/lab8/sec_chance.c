#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <stdbool.h>

typedef struct {
    int pageno;
    int chance;
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
         cache[i].chance = 0;
    }

    printf("Page Number that was not found: ");
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        totalRequests++;

        for (i=0; i < CACHE_SIZE - 1; i++)
            if (cache[i].pageno == page_num){
                foundInCache = true;
                cache[i].chance = 1;
                break; //break out loop because found page_num in cache
            }
        
        if (foundInCache == false){
            //You may print the page that caused the page fault
            totalFaults++;
            for(i = cache_i; i < CACHE_SIZE - 1; i++){
                if(cache[i].chance == 1){
                    cache[i].chance = 0; 
                    //cache_i;
                    if(cache_i == CACHE_SIZE - 1){
                        cache_i = 0;
                        i = 0; 
                    }
                }
                else{
                    cache[cache_i].pageno = page_num;
                    cache[cache_i].chance = 0; 
                    cache_i = (cache_i + 1) % CACHE_SIZE; //Need to keep the value within the cacheSize
                    printf("%d ", page_num);
                }
            }
        }
    }

    double missRate = totalFaults / (double)totalRequests;
    double hitRate = 1 - missRate;
    printf("\n%d Total Requests \n%d Total Page Faults \n%0.3f Miss Rate \n%0.3f Hit Rate\n", totalRequests, totalFaults, missRate, hitRate);
    return 0;
}
