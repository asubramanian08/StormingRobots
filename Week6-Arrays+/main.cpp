#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
// Chapter 8 page 180 number 13
void q1(void)
{
    char first;
    char last[20] = {0};
    printf("Enter a first and last name: ");
    char i;
    while ((i = getchar()) == ' ')
        ; // skip leading spaces
    first = i;

    while (getchar() != ' ')
        ;
    while ((i = getchar()) == ' ')
        ; // skip remaining spaces

    int j = 1;
    last[0] = i;
    do
    {
    } while (isalpha(last[j++] = getchar()));
    last[j - 1] = 0;

    printf("You entered the name: %s, %c\n", last, first);
}

// Chapter 8 page 180 number 14
void q2(void)
{
    char sentence[100] = {0};
    int wordStart[10] = {0};
    int count = 0;
    int wordCount = 0;
    printf("Enter a sentence: ");
    char i = getchar();
    while (i != '\n')
    {
        sentence[count] = i;
        if (count == 0 || (isalpha(sentence[count]) && sentence[count - 1] == ' '))
        {
            wordStart[wordCount] = count;
            wordCount++;
        }
        count++;
        i = getchar();
    }
    printf("Reversal of sentence:");
    count--;
    for (wordCount--; wordCount >= 0; wordCount--)
    {
        printf(" ");
        while (sentence[wordStart[wordCount]] != ' ' && wordStart[wordCount] < count)
        {
            printf("%c", sentence[wordStart[wordCount]]);
            wordStart[wordCount]++;
        }
    }
    printf("%c\n", sentence[count]);
}
// Chapter 8 page 180 number 15
void q3(void)
{
    char input[80];
    printf("Enter message to be encrypted: ");
    int count = 0;
    char letter = getchar();
    while (letter != '\n')
    {
        input[count] = letter;
        letter = getchar();
        count++;
    }
    printf("Enter shift amount (1-25): ");
    int shift = 0;
    letter = getchar();
    while (letter != '\n')
    {
        shift = (shift * 10) + (letter - '0');
        letter = getchar();
    }
    printf("Encrypted message: ");
    int goUp = 0;
    for (; goUp < count; goUp++)
    {
        if (input[goUp] <= 'Z' && input[goUp] >= 'A')
        {
            printf("%c", ((input[goUp] - 'A') + shift) % 26 + 'A');
        }
        else if (input[goUp] <= 'z' && input[goUp] >= 'a')
        {
            printf("%c", ((input[goUp] - 'a') + shift) % 26 + 'a');
        }
        else
        {
            printf("%c", input[goUp]);
        }
    }
    printf("\n");
}
// Chapter 8 page 181 number 16
void q4(void)
{
    int first[26] = {0};
    printf("Enter first word: ");
    char ch = getchar();
    while (ch != '\n')
    {
        first[ch - 'a']++;
        ch = getchar();
    }
    printf("Enter second word: ");
    ch = getchar();
    while (ch != '\n')
    {
        first[ch - 'a']--;
        ch = getchar();
    }
    int i;
    for (i = 0; first[i] == 0 && i <= 25; i++)
        ;
    if (i == 26)
    {
        printf("The words are anagrams. \n");
    }
    else
    {
        printf("The words are not anagrams. \n");
    }
}
// online question 1
void q5(void)
{
    int input[100];
    printf("Enter a list: ");
    int listLen = 0;
    char num = getchar();
    int number = 0;
    while (num != '\n')
    {
        if (num == ' ')
        {
            input[listLen] = number;
            listLen++;
            input[listLen] = -1;
            listLen++;
            number = 0;
        }
        else
        {
            number = (number * 10) + (num - '0');
        }
        num = getchar();
    }
    input[listLen] = number;
    printf("The reverse is: ");
    int goDown = listLen;
    for (; goDown >= 0; goDown--)
    {
        if (input[goDown] == -1)
        {
            printf(" ");
        }
        else
        {
            printf("%d", input[goDown]);
        }
    }
    printf("\n");
}
// online question 2
void q6(void)
{
    char a[26];
    for (int i = 0; i < 26; i++)
    {
        a[i] = i + 'A';
        printf("%c", a[i]);
    }
}
// online question 3
void q7(void)
{
    printf("Enter first letter: ");
    int letter = getchar();
    letter = letter - 'A';
    char a[26];
    int count = 1;
    for (int i = letter; i < 26; i++)
    {
        if (count % 5 == 0)
        {
            a[i] = i + 'a';
        }
        else
        {
            a[i] = i + 'A';
        }
        printf("%c ", a[i]);
        count++;
    }
    printf("\n");
}
// online question 4
void q8(void)
{
    printf("Enter a word: ");
    char list[100];
    int list$[199] = {0};
    char input = getchar();
    int count = 0;
    int goUp = 0;
    int points = 0;
    while (input != '\n')
    {
        list[count] = input;
        count++;
        input = getchar();
    }
    while (goUp < count)
    {
        if (list[goUp] == toupper(list[goUp]))
        {
            list$[goUp * 2] += 2;
            points += 2;
        }
        list[goUp] = tolower(list[goUp]);
        switch (list[goUp])
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'y':
            list$[goUp * 2] += 5;
            points += 5;
            break;
        case 'x':
        case 'q':
        case 'z':
            list$[goUp * 2] += 20;
            points += 20;
            break;
        default:
            list$[goUp * 2] += 10;
            points += 10;
            break;
        }
        if (goUp != count - 1)
        {
            list$[goUp * 2 + 1] = -1;
        }
        if ((list$[goUp * 2] - 2) % 5 == 0)
        {
            list[goUp] = toupper(list[goUp]);
        }
        goUp++;
    }
    goUp = 0;
    while (goUp < count)
    {
        printf("%c", list[goUp]);
        goUp++;
    }
    printf(" is worth %d points (", points);
    goUp = 0;
    while (goUp <= (count * 2 - 2))
    {
        if (list$[goUp] == -1)
        {
            printf("+");
        }
        else
        {
            printf("%d", list$[goUp]);
        }
        goUp++;
    }
    printf(")\n");
}
// online question 5
void q9(void)
{
#define MAXR 25
#define MAXC 20
    int abc[MAXR][MAXC];
    int rows = sizeof(abc) / sizeof(abc[0]);
    int cols = sizeof(abc[0]) / sizeof(abc[0][0]);
    printf("Rows: %d \nColumns: %d\n", rows, cols);
}
// online question 6
void q10(void)
{
    enum enDir
    {
        N,
        NE,
        E,
        SE,
        S,
        SW,
        W,
        NW
    };
    char sDir[NW + 1][10] = {"North    ", "NorthEast", "East     ", "SouthEast", "South    ", "SouthWest", "West     ", "NorthWest"};
    enDir d;                                 // like saying int d; now d can only = N - NW
    for (d = N; d <= NW; d = (enDir)(d + 1)) // The (enDir) is casting
    {
        printf("%s ==%d degrees\n", sDir[d], ((int)d) * 45);
    }
}
// online question 7
void q11(void)
{
    for (int j = 5, vowels[5] = {'u', 'o', 'i', 'e', 'a'}, age = 30; j > 0; j--, age -= 4)
    {
        printf("Daughter Beth%c   %d\nSon      Dennis%c %d\n", vowels[j - 1], age, vowels[j - 1], age - 2);
    }
}
// online question 8
void q12(void)
{
    printf("Enter row# column#: ");
    int row = 10;
    int column = 10;
    char i = getchar();
    while (i != '\n')
    {
        if (i >= '0' && i <= '9')
        {
            if (row == 10)
            {
                row = i - '0';
            }
            else
            {
                column = i - '0';
            }
        }
        i = getchar();
    }
    printf("Cell(%d,%d) = %d\n", row, column, (row * 6) + column + 1);
}
// online question 9
void q13(void)
{
    printf("Enter a number: ");
    char input = getchar();
    int i = 0;
    int factorial = 1;
    while (input != '\n')
    {
        i = (i * 10) + (input - '0');
        input = getchar();
    }
    for (; i > 1; i--)
    {
        factorial *= i;
    }
    printf("Factorial = %d\n", factorial);
}
// online question 10
void q14(void)
{
    int num1 = 1;
    int num2 = 1;
    printf("Enter a number: ");
    char input = getchar();
    int num = 0;
    while (input != '\n')
    {
        num = (num * 10) + (input - '0');
        input = getchar();
    }
    printf("In fibonacci - ");
    if (num <= 2)
    {
        printf("1\n");
        return;
    }
    for (short i = 2; i < num; i++)
    {
        num1 = num1 + num2;
        num2 = num1 - num2;
    }
    printf("%d\n", num1);
}
int main(void)
{
    //q1();
    //q2();
    //q3();
    //q4();
    //q5();
    //q6();
    //q7();
    //q8();
    //q9();
    //q10();
    q11();
    //q12();
    //q13();
    //q14();
    system("pause");
    return 0;
}