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
void calc_date(unsigned long inputSec){
    int month = 0, day = 0, year = 0, hour = 0, minutes = 0, seconds = 0, startYear = 1949, weeks = 0, rem = 0;

    year = inputSec / 31536000;
    rem = inputSec % 31536000;
    
    
    //weeks = rem / 604800;
    //rem = rem % 604800;
    
    
    day = rem / 86400;
    rem = rem % 86400;
    
    switch(1){
    	case(day <= 31):
        	month = 1;
            break;
        case(day <= 59):
        	month = 2;
            break;
        case(day <= 90):
        	month = 3;
            break;
        case(day <= 120):
        	month = 4;
            break;
        case(day <= 151):
        	month = 5;
            break;
        case(day <= 181):
        	month = 6;
            break;
        case(day <= 212):
        	month = 7;
            break;
         case(day <= 243):
         	month = 8;
            break;
        case(day <= 273):
        	month = 9;
            break;
        case(day <= 304):
        	month = 10;
            break;
        case(day <= 334):
        	month 11;
            break;
        case(day <= 365):
        	month 12;
            break;
    }

    hour = rem / 3600;
    rem = rem % 3600;
    
    minutes = rem / 60;
    rem = rem % 60;
 	
    seconds = rem;
    








    year += startYear;

    printf("\n%d %d %d %d %d %d\n", year, month, day, hour, minutes, seconds);
    //printf("\n%d/%d/%d %d:%d:%d", month, day, year, hour, minutes, seconds);
}