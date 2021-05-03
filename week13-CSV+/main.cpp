#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
/*struct tm {
	int tm_sec;   // seconds after the minute - [0, 60] including leap second
	int tm_min;   // minutes after the hour - [0, 59]
	int tm_hour;  // hours since midnight - [0, 23]
	int tm_mday;  // day of the month - [1, 31]
	int tm_mon;   // months since January - [0, 11]
	int tm_year;  // years since 1900
	int tm_wday;  // days since Sunday - [0, 6]
	int tm_yday;  // days since January 1 - [0, 365]
	int tm_isdst; // daylight savings time flag
};*/
void updateTime(void)
{
    time_t now;
    char times[100];
    tm timeinfo;
    timeinfo.tm_sec = 0;
    memset(&timeinfo, 0, sizeof(timeinfo));
    time(&now);
    timeinfo = *localtime(&now);
    printf("%ld,", now);
    //asctime_s(times, sizeof(timeinfo), timeinfo);
    //printf("Current local Date and Time: %s\n", times);
    //printf("[%d %d %d %d:%d:%d]\n", timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
void SSN(void)
{
    union SSN
    {
        struct broken
        {
            char num1[3];
            char dash1;
            char num2[2];
            char dash2;
            char num3[4];
        } separate;
        char entire[13];
    } whole;

    printf("enter you social security number: ");
    //scanf_s("%d-%d-%d", &whole.seppreate.num1, &whole.seppreate.num2, &whole.seppreate.num3);
    fgets(whole.entire, 13, stdin);
    //printf("%l\n", whole.wholeNum);
    printf("Region: %.3s\nGroup: %.2s\nSerial Number: %.4s\n", whole.separate.num1, whole.separate.num2, whole.separate.num3);
}
void whatColor()
{
    printf("Enter the hex version of the color's power: ");
    //int bob;
    union MyUnion
    {
        struct alone
        {
            int red : 2;
            int blue : 2;
            int green : 2;
        } colors;
        unsigned long allColor : 6;
    } RGB;
    //scanf_s("%lx", &(RGB.allColor));
    //printf("    Hex    Dec\nR = %x or %d\nB = %x or %d\nG = %x or %d\n", RGB.colors.red, RGB.colors.red, RGB.colors.blue, RGB.colors.blue, RGB.colors.green, RGB.colors.green);
}
void dealCards(void)
{
    enum suit
    {
        spade = 0,
        club = 1,
        heart = 2,
        diamond = 3
    };
    enum num
    {
        j = 9,
        q,
        k,
        a
    };
    //num bla = (num)1;
    //suit now = suit(1);
    //printf("%d", bla);
    //	now
    struct card
    {
        suit first;
        num sec;
    } save;
    card deck[52];
    for (int i = 0; i < 4; i++) //making deck
    {
        for (int j = 0; j < 13; j++)
        {
            deck[(i * 13) + j].first = (suit)i;
            deck[(i * 13) + j].sec = (num)j;
        }
    }
    int hold = 0;
    for (int i = 0; i < 52; i++)
    {
        hold = rand() % 52;
        save.first = deck[i].first;
        save.sec = deck[i].sec;
        deck[i].first = deck[hold].first;
        deck[i].sec = deck[hold].sec;
        deck[hold].first = save.first;
        deck[hold].sec = save.sec;
    };
    for (int i = 0; i < 4; i++) //dealing deck
    {
        printf("PERSIONl: %d\n", i);
        for (int j = 0; j < 13; j++)
        {
            printf("%d, ", deck[(i * 13) + j].first) + 1;
            //deck[(i * 12) + j].sec;
            printf("%d\n", deck[(i * 13) + j].sec + 1);
        }
    }
}
void changeColor(void)
{
    printf("Enter a number from 0-6 to change the color: ");
    int command_line = getchar() - '0';
    char string[20];
    sprintf(string, "color %d%x", command_line, command_line + 8);
    system(string);
}
void displayTime()
{
    printf("enter seconds: ");
    time_t start;
    time(&start);
    time_t now;
    time(&now);
    tm timeinfo;
    int total = 0;
    char ch = getchar();
    while (ch != '\n')
    {
        total = total * 10 + ch - '0';
        ch = getchar();
    }
    while ((int)now - total != start)
    {
        const int segments[10][9] =
            {{0, 1, 0, 1, 0, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 1, 1, 1, 1, 0}, {0, 1, 0, 0, 1, 1, 0, 1, 1}, {0, 0, 0, 1, 1, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 0, 0, 1, 1}, {0, 1, 0, 1, 1, 0, 1, 1, 1}, {0, 1, 0, 0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 1, 1, 1, 1, 1}, {0, 1, 0, 1, 1, 1, 0, 1, 1}};
        //printf("Enter a number: ");
        //char x = getchar();
        int userNumber[10] = {0};
        timeinfo = *localtime(&now);
        int where;
        if (timeinfo.tm_hour % 12 > 9)
        {
            where = 2;
            userNumber[0] = (timeinfo.tm_hour % 12) / 10;
            userNumber[1] = (timeinfo.tm_hour % 12) % 10;
        }
        else
        {
            where = 1;
            userNumber[0] = (timeinfo.tm_hour % 12);
        }
        userNumber[where] = timeinfo.tm_sec / 10;
        userNumber[where + 1] = timeinfo.tm_sec % 10;
        int j = where + 2;

        //for each "line" of the output
        for (int z = 0; z < 3; z++)
        {
            //for each number that needs to be printed
            for (int b = 0; b < j; b++)
            {
                //for each character
                for (int k = 3 * z; k < (3 * (z + 1)); k++)
                {
                    if (segments[userNumber[b]][k] == 0)
                        printf(" ");
                    else if (k % 3 == 1)
                        printf("_");
                    else
                        printf("|");
                }
                printf(" ");
            }
            printf("\n");
        }
        time(&now);
    }
    return;
}
void canAccess(void)
{
    char ch;
    while ((ch = getchar()) != '\n')
    {
        int access = 0x0000;
        //char read[7] = "can";
        //char write[7] = "can";
        //char execute[7] = "can";
        char Return[3][18] = {"cannot read | ", "cannot write | ", "cannot execute\n"};
        int i = 3;
        while (ch != ' ')
        {
            ch = getchar();
        } //the name of the program
        ch = getchar();
        while ((ch != '\n') && (i--))
        {
            if ((ch != '1') && (ch != '0'))
            {
                printf("bad input!");
                return;
            }
            access |= (ch - '0') << i;
            ch = getchar();
        }
        if (ch != '\n')
        {
            printf("bad input!");
            return;
        }
        for (int j = 2; j >= i; j--)
        {
            if (access & 1 << j)
            {
                int size = strlen(Return[2 - j + i]);
                memmove(&Return[2 - j + i][3], &Return[2 - j + i][6], size);
                Return[2 - j + i][size] = '\0';
            }
        }
        printf("%s%s%s", Return[0], Return[1], Return[2]);
    }
}

int main1(void)
{

    //updateTime();//done
    //SSN(); //done
    //dealCards(); //done
    //whatColor //done
    //changeColor(); //done
    //displayTime(); //done
    //test();
    //canAccess();
    /*typedef struct {
		int ia1;    // 0-3   
		char c1;  // 4, but 5 padded  
		short ia2;  // 6-7  
		short ia3;   // 8, but 9-11 padded 
	} TILE[0]
	printf("%d", sizeof(TILE));*/
    system("pause");
    return 0;
}
