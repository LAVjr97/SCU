// Name: Luis Villalta
// Date: 3/17/24
// Title: Lab 9 - Step 2
// Description: This program uses a fixed buffer size of 10000 bits, to read a given file. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main(int argc, char *argv[]){
    char buffer[10000];
    FILE *fp;

    fp = fopen(argv[1], "rb");
    while (fread(buffer, sizeof(buffer), 1, fp)){}
    fclose(fp);
    return 0;
}