/*
Write a program that prompts you to enter RGB color values where each of red, green, and blue
is an integer between 0 and 255. If you enter an incorrect number, report an input error.
Otherwise, compute the equivalent HSL color value and print it out. You can find the formulae,
examples, and a tester here.

https://www.rapidtables.com/convert/color/rgb-to-hsl.html
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int i, cmaxIndex, cminIndex;
float r, g, b, h, s, l, cmax = -1, cmin = 256, delta;
float rgbp[3];

float hueCalc(void);
float saturationCalc(void);
float lightnessCalc(void);

int main(void){
    printf("Enter a Red Value: ");
    scanf("%f", &r);
    if(r < 0 || r > 255)
        printf("Error! A number less than 0 or greater than 255 was given!\n");

    printf("Enter a Green Value: ");
    scanf("%f", &g);
    if(g < 0 || g > 255)
        printf("Error! A number less than 0 or greater than 255 was given!\n");

    printf("Enter a Blue Value: ");
    scanf("%f", &b);
    if(b < 0 || b > 255)
        printf("Error! A number less than 0 or greater than 255 was given!\n");

    rgbp[0] = r/255;
    rgbp[1] = g/255;
    rgbp[2] = b/255;

    for(i = 0; i < 3; i++){
        if(rgbp[i] > cmax){
            cmax = rgbp[i];
            cmaxIndex = i;
        }
    }
    for(i = 0; i < 3; i++){
        if(rgbp[i] < cmin){
            cmin = rgbp[i];
            cminIndex = i;
        }      
    }

    delta = cmax - cmin;
    
    l = lightnessCalc();
    h = hueCalc();
    s = saturationCalc();

    l *= 100;
    
    printf("H:%.0f°, S:%.0f%%, L:%.0f%%", h, s, l);
    return 0;
}

float hueCalc(void){
    float result = 0;

    if(delta == 0)
        return result;

    if(cmaxIndex == 0){ //Red
        result = (rgbp[1] - rgbp[2]) / delta;
        if(result < 0)
            result += 6;
        result *= 60;

        return result;
    }

    if(cmaxIndex == 1){ //Green
        result = (rgbp[2] - rgbp[0]) / delta;
        result += 2;
        result *= 60;

        return result;
    }

    if(cmaxIndex == 2){ //Blue
        result = (rgbp[0] - rgbp[1]) / delta;
        result += 4;
        result *= 60;
    }

    return result;

}

float saturationCalc(void){
    float result = 0;

    if(delta == 0)
        return result;

    if(delta < 0 || delta > 0){
        result = 2*l;
        result -= 1;
        result = fabsf(result);
        result = 1 - result;
        result = delta / result;
    }

    result *= 100;
    return result;
}

float lightnessCalc(void){
    float result;

    result = cmax + cmin;
    result /= 2;

    return result;
}