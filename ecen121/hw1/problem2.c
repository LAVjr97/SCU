#include <stdio.h>

void calcDate(unsigned long seconds);

int main(void){
    unsigned long seconds;
    printf("Please enter the amount of seconds: ");
    scanf("%lu", &seconds);

    calcDate(seconds);

    return 0;
}

/*Print out the month, day, year, and time.
    31,536,000 seconds in a year, 
    86,400 in a day,
    3,600 in an hour
*/

void calcDate(unsigned long inputSec){
    int month = 0, day = 0, year = 0, hour = 0, minutes = 0, seconds = 0, startYear = 1949, rem = 0, i = 0;
    int leapDay = 0; 

    year = inputSec / 31536000;
    rem = inputSec % 31536000;

    int leapYears = (year + 1) / 4; //1953 is the closest leap year

    if(leapYears > 0){ 
        leapDay = 1;
        rem = rem - (86400 * (leapYears ));
    }
    printf("%d", leapYears);
    //number of days in the year
    day = rem / 86400;
    rem = rem % 86400;

    //if(rem)
    //    day++;

    int daysInMonth[12] = {31, 28 + leapDay, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


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
71031077
9/10/1969 14:47:47*/