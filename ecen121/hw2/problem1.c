/*
Write a program that includes an array of 120 unsigned integers. Fill that array with one cycle of
a sine wave scaled for use with an A/D converter such that the A/D converter input value ranges
from 0-4095.
Next, print out that array as a C data structure to a file called sindat.h – an initialized array of
integers, such that it can be included in another C program. The output is source code that could
be included directly into another C program. Test the output to make sure it is proper C code.
*/

#include <stdio.h>
#include <math.h>

int main(void){
    unsigned int wave[120];
    int i;
    float angle, sine;
    FILE *file;
    
    for(i = 0; i < 120; i++){
        angle = (2 * 3.14159 * i) / 120;
        sine = (sin(angle) + 1) / 2;
        wave[i] = sine * 4095;
    }

    file = fopen("sindat.h", "w");
    
    fprintf(file, "unsigned int wave[120] = {");
    for(i = 0; i < 120; i++){
        fprintf(file,"%u", wave[i]);
        if(i < 119)
            fprintf(file, ", ");
    }

    fprintf(file, "};");
    fclose(file);

    return 0;
}