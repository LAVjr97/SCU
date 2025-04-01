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
    86,400 in a day,
    3,600 in an hour
*/

void calc_date(unsigned long inputSec){
    int month = 0, day = 0, year = 0, hour = 0, minutes = 0, seconds = 0, startYear = 1949, rem = 0, i = 0;
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    year = inputSec / 31536000;
    rem = inputSec % 31536000;
    
    //number of days in the year
    day = rem / 86400;
    rem = rem % 86400;

    if(rem)
        day++;

    //day is compared to the number of days in a given month,
    while(day >= daysInMonth[i]){
        day -= daysInMonth[i];
        i++;
    }

    month = i + 1;

    hour = rem / 3600;
    rem = rem % 3600;
    
    minutes = rem / 60;
    rem = rem % 60;
 	
    seconds = rem;

    year += startYear;

    printf("\n%d/%d/%d %d:%d:%d", month, day, year, hour, minutes, seconds);
}


/*Please enter the amount of seconds: 652546067

9/10/1969 14:47:47*/