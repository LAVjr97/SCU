#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

typedef struct {
int pageno;
. . .
} ref_page;
ref_page cache[cacheSize]; // Cache that stores pages
char pageCache[100]; // Cache that holds the input from test file
int totalFaults = 0; // keeps track of the total page faults





int main(int argc, char *argv[]){
	int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
    }

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
    	bool foundInCache = false;
        for (i=0; i<cacheSize; i++){
            if (cache[i].pageno == page_num){
                foundInCache = true;
                break; //break out loop because found page_num in cache
            }
        }
        if (foundInCache == false){
            //You may print the page that caused the page fault
            cache[placeInArray].pageno = page_num;
            totalFaults++
            placeInArray++; //Need to keep the value within the cacheSize
        }
    }

    printf("%d Total Page Faults", totalFaults);
    return 0;
}

//Cache Size 50
//FIFO: 9595
//LRU: 9595
//