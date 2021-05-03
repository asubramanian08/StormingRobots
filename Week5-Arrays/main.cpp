#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
// first practice problem
void practice1(void)
{
    printf("Enter letter: ");
    char letter = getchar();
    char endLetter = letter;
    int i, j;
    for (j = 0; endLetter != ('Z' + 1); j++)
    {
        for (i = 0, endLetter = letter; i <= j; i++, endLetter++)
        {
            printf("%c", endLetter);
        }
        printf("\n");
    }
}
// second practice problem
void practice2(void)
{
    printf("Enter letter: ");
    char letter = getchar();
    int i, j;
    for (j = 0; letter != ('Z' + 1); j++)
    {
        for (i = 0; i <= j && letter <= 'Z'; i++, letter++)
        {
            printf("%c", letter);
        }
        printf("\n");
    }
}
// Chaptor 8 Pg 178 Number 1
void q1(void)
{
    int digit_seen[10] = {false};
    printf("Enter a number: ");
    char i;
    while ((i = getchar()) != '\n')
    {
        i = i - '0';
        if (digit_seen[i])
        {
            digit_seen[i] = 2;
        }
        else
        {
            digit_seen[i] = 1;
        }
    }
    printf("Digit(s) repeated:");
    for (int i = 0; i < 10; i++)
    {
        if (digit_seen[i] == 2)
        {
            printf("%2d", i);
        }
    }
    printf("\n");
}
// Chaptor 8 Pg 178 Number 2
void q2(void)
{
    int digit_seen[10] = {false};
    printf("Enter a number: ");
    char i;
    while ((i = getchar()) != '\n')
    {
        digit_seen[i - '0']++;
    }
    printf("Digit:        0  1  2  3  4  5  6  7  8  9\nOccurrences:");
    for (int i = 0; i < 10; i++)
    {
        printf("%3d", digit_seen[i]);
    }
    printf("\n");
}
// Chaptor 8 Pg 179 Number 7
void q3(void)
{
    int x = 0;
    int row[5] = {0}, column[5] = {0};
    int currentNum = 0;
    int z = 0;
    for (int i = 1; i < 6; i++)
    {
        printf("Enter row %d: ", i);
        char j = getchar();
        while (1)
        {
            if (j == ' ')
            {
                row[i - 1] += currentNum;
                column[x] += currentNum;
                currentNum = 0;
                x++;
            }
            else
            {
                if (j == '\n')
                {
                    row[i - 1] += currentNum;
                    column[x] += currentNum;
                    break;
                }
                currentNum = (currentNum * 10) + (j - '0');
            }
            j = getchar();
        }
        x = 0;
        currentNum = 0;
    }
    printf("Row totals: ");
    for (; z < 5; z++)
    {
        printf("%3d", row[z]);
    }
    z = 0;
    printf("\nColumn totals: ");
    for (; z < 5; z++)
    {
        printf("%3d", column[z]);
    }
    printf("\n");
}
// Chaptor 8 Pg 179 Number 9
void q4(void)
{
    while (1)
    {
        int arrays[10][10] = {'A'};
        int rows = 0;
        int cols = 0;
        int random;
        char letter;
        int count = 0;
        srand((unsigned)time(NULL));
        random = rand() % 4;
        for (letter = 'B'; letter <= 'Z' && count < 4; letter++)
        {
            while (arrays[rows][cols] != letter)
            {
                switch (random)
                {
                case 0:
                    if ((rows - 1 >= 0) && (arrays[rows - 1][cols] == false))
                    {
                        rows--;
                        arrays[rows][cols] = letter;
                        count = 0;
                        break;
                    }
                    count++;
                case 1:
                    if ((cols + 1 <= 9) && (arrays[rows][cols + 1] == false))
                    {
                        cols++;
                        arrays[rows][cols] = letter;
                        count = 0;
                        break;
                    }
                    count++;
                case 2:
                    if ((rows + 1 <= 9) && (arrays[rows + 1][cols] == false))
                    {
                        rows++;
                        arrays[rows][cols] = letter;
                        count = 0;
                        break;
                    }
                    count++;
                case 3:
                    if ((cols - 1 >= 0) && (arrays[rows][cols - 1] == false))
                    {
                        cols--;
                        arrays[rows][cols] = letter;
                        count = 0;
                        break;
                    }
                    count++;
                }
                if (count >= 4)
                {
                    break;
                }
                else if (count != 0)
                {
                    random = 0;
                    continue;
                }
                random = rand() % 4;
            }
            continue;
        }
        printf("Random path:\n");
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (arrays[i][j] == false)
                {
                    arrays[i][j] = '.';
                }
                printf("%3c", arrays[i][j]);
            }
            printf("\n");
        }
        printf("Do you want to go again? if so click space then enter else click enter: ");
        int i = getchar();
        if (i == '\n')
        {
            return;
        }
        while (i != '\n')
        {
            i = getchar();
        }
    }
}
int main(void)
{
    //practice1();
    //practice2();
    //q1();
    //q2();
    //q3();
    q4();
    system("pause");
    return 0;
}