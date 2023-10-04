#define high 8; 

typedef struct{
    int array[8];
}numbers;

numbers a;

void main()
{
    if(n > m){
        i = partition(a, m, n);
        quickSort(a, m, i);
        quickSort(a, i+ 1, n);
    }



    readArray();
    // dont forget to change 8 to high
    quickSort(a, 1, 8);
    writeArray();

}
void readArray()
{
    int i;
    for(i = 0; i < 8; i++) 
        printf("%d ", a.array[i]);
    printf("\n");

    return;
}
   
void writeArray()
{
    int i;
    //remember to change this back to high ot figure this shit out
    for(i = 0; i < 8; i++)
        printf("%d ", a.array[i]);
    printf("\n");

    return;
}

void quickSort(numbers a, int m, int n)
{
    int i;
    return;
}

int partition(numbers a, int y, int z)
{
    int i, j, x;

    x = a.array[y];
    i = y - 1;
    j = z + 1;

    while(i < j){
        do 
            j = j -1;
        while(a.array[j] <= x);

        do 
            i = i + 1;
        while(a.array[i] <= x);

        if(i < j)
            exchange(a.array[i], a.array[j]);
    }
    
    return j;
}

void exchange(int a, int b)
{
    int t;
    t = a;
    a = b;
    b = t;
    return;
}

