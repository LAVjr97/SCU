// Name: Luis Villalta
// Date: 3/10/24
// Title: Lab 8 Memory Management
// Description: This program implements Least Recently Used (LRU) algorithm for page replacement

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
    int totalRequests = 0, i, j, cache_i, oldest, oldest_i;
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array
         cache[i].pageno = -1;
         cache[i].age = 0;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        totalRequests++;
        oldest = 0;

        for (i=0; i < CACHE_SIZE; i++){
            cache[i].age++;
            if (cache[i].pageno == page_num){ //if page number is found in cache
                foundInCache = true;
                cache[i].age = 0;
            }
            if(cache[i].age > oldest){ //update the oldest page in cache and store its index
                oldest_i = i;
                oldest = cache[i].age;
            }
        }   

        if (foundInCache == false){
            cache[oldest_i].pageno = page_num; //insert page number at oldest
            cache[oldest_i].age = 0; //set age to 0
            totalFaults++;
            printf("%d\n", page_num);
        }
    }

    double missRate = totalFaults / (double)totalRequests;
    double hitRate = 1 - missRate;
    //printf("\n%d Total Requests \n%d Total Page Faults \n%0.3f Miss Rate \n%0.3f Hit Rate\n", totalRequests, totalFaults, missRate, hitRate);
    return 0;
}