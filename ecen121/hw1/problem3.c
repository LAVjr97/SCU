#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void sort(char **slist, size_t length);
int compStrings(const void *l, const void *r);

int main(void){
    char str1[] = "Andrew ";
    char str2[] = "aardvark ";
    char str3[] = "airplanes";
    char str4[] = "America";
    char str5[] = "air ball";
    char str6[] = "Air Canada";
    char str7[] = "airplane";
    char str8[] = "Air Pod";
    char str9[] = "apple";
    char str10[] = "advantage";
    char *slist[10] = {str1, str2, str3, str4, str5, str6, str7, str8, str9, str10};

    size_t length = sizeof(slist) / sizeof(slist[0]);
    sort(slist, length);
    
    
}

void sort(char **slist, size_t length){
    int i = 0, j;
    qsort(slist, length, sizeof(char*), compStrings);

    while(i < length){
        j = 0;
        while(slist[i][j] != '\0'){
            printf("%c", slist[i][j]);
            j++;
        }
        printf("\n");
        ++i;
    }
}

int compStrings(const void *l, const void *r){
    char *stringL = *(char**)l;
    char *stringR = *(char**)r;

    return strcasecmp(stringL, stringR);
}