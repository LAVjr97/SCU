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
    
    printf("Test 1\n");
    sort(slist, length);

    printf("\nTest 2\n");
    
    char str11[] = "Hello";
    char str12[] = "Dog";
    char str13[] = "Cat";
    char str14[] = "rabbit";
    char str15[] = "man";
    char str16[] = "woman";
    char str17[] = "person";
    char str18[] = "camera";
    char str19[] = "TV";
    char str20[] = "clueless";
    char *slist1[10] = {str11, str12, str13, str14, str15, str16, str17, str18, str19, str20};

    length = sizeof(slist1) / sizeof(slist1[0]);
    sort(slist1, length);
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