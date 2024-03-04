#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[sizeof(int)]; 
    int i;
    fp = fopen("testInput.txt", "w");
    for (i=0; i<50; i++){
        sprintf(buffer, "%d\n", rand()%10);
        fputs(buffer, fp);
    }
    fclose(fp);
    return 0;
}