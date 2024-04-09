#ifndef __DATE__CONTROLLERS__
#define __DATE__CONTROLLERS__

#include <iostream>
#include <string.h>

#include "models.h"
#include "../../utils/String.h"
#include "../../utils/UserInterface.h"
#include "../../utils/Mylibrary.h"

void InputDate(PDate pDate, bool filter = false)
{
    char hour[2], minute[2];
    char day[2], month[2], year[4]; 
    int x = wherex();
    int y = wherey();
    bool isValidDate = false;

    while(!isValidDate)
    {
        ShowCursor(true);
        gotoxy(x,y);    
        char *str;
        if(filter == false) {
        	std::cout <<"  :   -   /  /    .";

        	gotoxy(x, y);
            str = Input(sizeof(hour), Number);
            strcpy(hour, str);
            pDate->hour = atoi(hour);
            freeMemmorry(str);

        	gotoxy(x+3,y);
            str = Input(sizeof(minute), Number);
            strcpy(minute, str);
            pDate->minute = atoi(minute);
            freeMemmorry(str);

        	gotoxy(x+8,y);
            str = Input(sizeof(day), Number);
            strcpy(day, str);
            pDate->day = atoi(day);
            freeMemmorry(str);

        	gotoxy(x+11,y);
            str = Input(sizeof(month), Number);
            strcpy(month, Input(sizeof(month), Number));
            pDate->month = atoi(month);
            freeMemmorry(str);

        	gotoxy(x+14,y);
            str = Input(sizeof(year), Number);
            strcpy(year, Input(sizeof(year), Number));
            pDate->year = atoi(year);
            freeMemmorry(str);
		}
		else {
			std::cout <<"   /  /    .";

			gotoxy(x+1,y);
            str = Input(sizeof(day), Number);
            strcpy(day, str);
            pDate->day = atoi(day); 
            freeMemmorry(str);

        	gotoxy(x+4,y);
            str = Input(sizeof(month), Number);
            strcpy(month, str);
            pDate->month = atoi(month);
            freeMemmorry(str);

        	gotoxy(x+7,y);
            str = Input(sizeof(year), Number);
            strcpy(year, str);
            pDate->year = atoi(year);
            freeMemmorry(str);
		}

        isValidDate = IsValidDate(pDate);
        if(isValidDate == false)
            Notification("Thoi gian khong hop le!");
    }
}

#endif