#include <stdio.h>

float mean(float *num);
float mode(float *num);
// float median(float *num);

int main(void){
    float num[15] = {0.0, 9.0, 1.3, 3.0, 2.23, 5.5, 30.6, 0.0, 7.4, 1.3, 15.9, 12.3, 8.4, 0.0, 1.5};

    printf("Mean: %f\n", mean(num));
    printf("Mode: %f\n", mode(num));
    // printf("Median: %f\n", median(num));

    return 0;
}

//Average
float mean(float *num){
    int i;
    float mean = 0;

    for(i = 0; i < 15; i++)
        mean += num[i];
    
    mean = mean / 15;

    return mean;
}

//Most Frequent
float mode(float *num){ 
    int i, j, maxC = 0, curC;
    float mode = 0;

    for(i = 0; i < 15; i++){
        curC = 0;

        for(j = 0; j < 15; j++)
            if(num[i] == num[j])
                curC++;
        
        if(curC > maxC){
            mode = num[i];
            maxC = curC;
        }
    }

    return mode;
}

//Middle when sorted
float median(float *num){
    float median;

    

    return median;
}