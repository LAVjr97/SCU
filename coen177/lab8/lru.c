#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <stdbool.h>

typedef struct {
    int pageno;
    int age;
} ref_page;

int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file
    int totalFaults = 0; // keeps track of the total page faults
    int totalRequests = 0, i, j, cache_i, oldest;
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array
         cache[i].pageno = -1;
         cache[i].age = 0;
    }

    printf("Page Number that was not found: ");
    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        totalRequests++;
        oldest = 0; 

        for (i=0; i < CACHE_SIZE - 1; i++)
            if (cache[i].pageno == page_num){
                foundInCache = true;
                for(j = 0; j < CACHE_SIZE - 1; j++) //increment the age of every page that is younger than the current page, because LRU
                    if(cache[i].age > cache[j].age) //treats it as a stack, so current cache[i] goes to the top, everything before it gets pushed down
                        cache[j].age++;

                cache[i].age = 0;
                break; //break out loop because found page_num in cache
            }

        if (foundInCache == false){
            //You may print the page that caused the page fault
            cache[cache_i].pageno = page_num;
            cache[cache_i].age = 0;
            totalFaults++;
            for(i = 0; i < CACHE_SIZE - 1; i++) 
                cache[i].age++;                //update age for all pages
                if(oldest < cache[i].age){     //if there is an older page than oldest, update oldest and cache_i
                    oldest = cache[i].age; 
                    cache_i = i;
                }

            cache_i = (cache_i + 1) % CACHE_SIZE; //Need to keep the value within the cacheSize
            printf("%d ", page_num);
        }
    }

    double missRate = totalFaults / (double)totalRequests;
    double hitRate = 1 - missRate;
    printf("\n%d Total Requests \n%d Total Page Faults \n%0.3f Miss Rate \n%0.3f Hit Rate\n", totalRequests, totalFaults, missRate, hitRate);
    return 0;
}