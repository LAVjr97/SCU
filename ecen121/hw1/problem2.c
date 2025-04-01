#include <stdio.h>

void calc_date(unsigned long seconds);


int main(void){
    unsigned long seconds;
    printf("Please enter the amount of seconds: ");
    scanf("%lu", &seconds);

    calc_date(seconds);

    return 0;
}

/*Print out the month, day, year, and time.
    31,536,000 seconds in a year, 
    604,800 seconds in a week
    86,400 in a day,
    3,600 in an hour
*/
void calc_date(unsigned long seconds){
    int month = 0, day = 0, year = 0, hour = 0, minutes = 0, seconds = 0, startYear = 1949;
    int week = 0; 

    year = 








    printf("\n%d/%d/%d %d:%d:%d", month, day, year, hour, minutes, seconds);
}