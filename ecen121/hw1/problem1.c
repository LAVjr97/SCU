#include <stdio.h>
#include <stdlib.h>

float mean(float *num);
float mode(float *num);
float median(float *num);

int compFloats(const void *l, const void *r);

int main(void){
    float num[15] = {0.0, 9.0, 1.3, 3.0, 2.23, 5.5, 30.6, 0.0, 7.4, 1.3, 15.9, 12.3, 8.4, 0.0, 1.5};

    size_t size = sizeof(num) / sizeof(float);
    qsort(num, size, sizeof(float), compFloats);

    printf("Mean: %f\n", mean(num));
    printf("Mode: %f\n", mode(num));
    printf("Median: %f\n", median(num));

    return 0;
}

//Average
float mean(float *num){
    int i;
    float mean = 0;

    for(i = 0; i < 15; i++)
        mean += num[i];

    return mean / 15;
}

//Most Frequent
float mode(float *num){ 
    int i, maxF = 0, curF = 0;
    float mode;

    for(i = 0; i < 14; i++){
        if(num[i] == num[i+1]) 
            curF++;
        
        else{
            if(curF > maxF){
                maxF = curF;
                mode = num[i];
            }
            curF = 1;
        }
    }

    return mode;
}

//Middle when sorted
float median(float *num){
    return num[8];
}

int compFloats(const void *l, const void *r){
    float floatL = *(float*)l;
    float floatR = *(float*)r;
    return (floatL > floatR) - (floatL < floatR);
}
