#include <stdio.h>

void calcDate(unsigned long seconds);

int main(void){
    unsigned long seconds;
    printf("Please enter the amount of seconds: ");
    scanf("%lu", &seconds);

    calcDate(seconds);
    return 0;
}

void calcDate(unsigned long inputSec){
    int month = 0, day = 0, year = 0, hour = 0, minutes = 0, seconds = 0, startYear = 1949, rem = 0, i = 0;
    int leapDay = 0; 

    year = inputSec / 31536000;
    rem = inputSec % 31536000;

    int leapYears = (year + 1) / 4; //1953 is the closest leap year
    int leapYearsRem = (year + 1) % 4; 
    
    if(!leapYearsRem) //If that year is a leap year, add an extra day to feb
        leapDay = 1;

    if(leapYears > 0)
        rem = rem - (86400 * (leapYears - leapDay));
    
    //number of days in the year
    day = rem / 86400;
    rem = rem % 86400;

    if(rem)
        day++;

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

    printf("%d/%d/%d %d:%d:%d", month, day, year, hour, minutes, seconds);
}
/*71031077
73292866
420696291
216085900
1591050919
1577964071
2298416818*/