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
        fwrite(buffer, sizeof(buffer), 1, fp);
    fclose(fp);    
    fclose(rp);
    return 0;
}