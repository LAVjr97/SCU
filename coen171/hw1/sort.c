#include <stdio.h>

#define high 8 

typedef int numbers[high];

numbers a;

void readArray()
{
    int i;

    for(i = 0; i < high; i++) 
        scanf("%d", &a[i]);
}
   
void writeArray()
{
    int i;

    for(i = 0; i < high; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void exchange(int *a, int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

int partition(int y, int z)
{
    int i, j, x;

    x = a[y];
    i = y - 1;
    j = z + 1;

    while(i < j){
        do 
            j--;
        while(a[j] > x);

        do 
            i++;
        while(a[i] < x);

        if(i < j)
            exchange(&a[i], &\
            a[j]);

    }
    return j;
}

void quickSort(int m, int n)
{
    int i;
    if(n > m){
        i = partition(m, n);
        quickSort(m, i);
        quickSort(i + 1, n);
    }
}

void main()
{
    readArray();
    quickSort(0, high - 1);
    writeArray();
}