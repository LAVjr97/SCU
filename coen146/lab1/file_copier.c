//  
//  Created by Behnam Dezfouli
//  CSEN, Santa Clara University
//  
//  
// This program offers two options to the user:
// -- Option 1: enables the user to copy a file to another file. 
// The user needs to enter the name of the source and destination files.
// -- Option 2: enables the user to measure the performance of file copy. 
// In addition to the name of source and destination files, the user needs to enter the maximum source file size as well as the step size to increment the source file size.
//
//
// double copier(FILE *s_file, FILE *d_file)
// Precondition: s_file is a pointer to a file opened in read mode, d_file is a file pointer opened in write mode
// Postcondition: Copies the contents of the file pointed to by s_file to the file pointed to by d_file
//


#include <stdio.h>
#include <stdlib.h> // For exit()
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1
#define DUM_CHAR 'A'

void funCopier(FILE *s_file, FILE *d_file)
{    
    char buf[1];
    size_t size = 1, count = 1;

    //as long as there's something to read in the file, it will copy 
    while(fread(buf, size, count, s_file) == 1)
        fwrite(buf, size, count, d_file);

    return;
}

void sysCopier(int s_file, int d_file){
    char buf[1];
    size_t size = 1;
    
    //as long as there's something to read in the file, it will copy 
    while(read(s_file, buf, size) == 1) 
        write(d_file, buf, size);

    return;
}

int main()
{
    int option;
    printf("1. File Copy \n2. File Copy With Performance Measurements\n");
    scanf("%d", &option);

    if ( option == 1 ) // File copy
    {
        char sourcef[20], destf[20]; 
        int call;

        printf("Enter the name of the source file: \n");
        scanf("%s", &sourcef[0]);
        printf("Enter the name of the destination file: \n");
        scanf("%s", &destf[0]); 

        printf("Which way do you want your file copied? \n1. Using function calls \n2. Using system calls\n");
        scanf("%d", &call);

        //options to use either function or system calls for copying
        if(call == 1){
            //opens the files to read from or write to
            FILE *s_file = fopen(sourcef, "r"); 
            FILE *d_file = fopen(destf, "w"); 

            funCopier(s_file, d_file);
        }
        else if(call == 2){
            //opens the files to read from or write to
            int sfile = open(sourcef, O_RDONLY);
            int dfile = open(destf, O_WRONLY | O_CREAT);

            sysCopier(sfile, dfile);
        }
        else
        {
            printf("Invalid option!");
            return 0;
        }
        printf("\nCopy has been made! \n");
    }
    
    else if ( option == 2 ) // File copy with performance measurement
    {
        char sourcef[20], destf[20] = "perf.txt"; 
        int bSize, current_size = 0, sSize, size = 1; 
        clock_t start, end;
        double cpu_time_used;  

        printf("Enter the name of the source file: \n");   
        scanf("%s", &sourcef[0]); 
        printf("Enter the maximum file size (bytes): \n"); 
        scanf("%d", &bSize); 
        printf("Enter the step size: \n"); 
        scanf("%d", &sSize);

        
        while (current_size < bSize)
        {   
            current_size += sSize;
            char buf[current_size];

            //writes empty bytes to the file
            FILE *s_file = fopen(sourcef, "w");
            fwrite(buf, size, current_size, s_file);
            fclose(s_file);

            //opens file to be read from or written to
            FILE *s_fil = fopen(sourcef, "r"); 
            FILE *d_fil = fopen(destf, "w"); 
            
            start = clock();
            funCopier(s_fil, d_fil); 
            end = clock(); 

            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
            printf("Time taken to copy the file: %f \n", cpu_time_used); 
        }

    }
    
    else
    {
        printf("Invalid option!"); 
        return 0;
    }
    
    return 0;
}