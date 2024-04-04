// Name: Luis Villalta
// Date: 3/17/24
// Title: Lab 9 - Step 4
// Description: This program reads from a file and writes to a new file given a buffer size and text file to read from. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main(int argc, char *argv[]){
    char buffer[atoi(argv[2])];
    FILE *fp, *rp;

    fp = fopen(argv[1], "rb");
    rp = fopen("step4Results.txt", "wb");
    while (fread(buffer, sizeof(buffer), 1, fp))
        fwrite(buffer, sizeof(buffer), 1, rp);
    fclose(fp);    
    fclose(rp);
    return 0;
}
	