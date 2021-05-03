#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>

// Chapter 7 page 158 question 5
void q1(void)
{
    printf("Enter a word:");
    int sum = 0;
    char letter = getchar();
    while (letter != '\n')
    {
        letter = toupper(letter);
        switch (letter)
        {
        case 'Q':
        case 'Z':
            sum += 10;
            break;
        case 'K':
            sum += 5;
            break;
        case 'J':
        case 'X':
            sum += 8;
            break;
        case 'F':
        case 'H':
        case 'V':
        case 'W':
        case 'Y':
            sum += 4;
            break;
        case 'D':
        case 'G':
            sum += 2;
            break;
        case 'B':
        case 'C':
        case 'M':
        case 'P':
            sum += 3;
            break;
        case 'A':
        case 'E':
        case 'I':
        case 'L':
        case 'N':
        case 'O':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
            sum += 1;
            break;
        default:
            printf("ERROR please enter a letter");
            break;
        }
        letter = getchar();
    }
    printf("Scrabble value: %d", sum);
}
// Chapter 7 page 158 question 6
void q2(void)
{
    printf("The size of an int is: %zu \nshort is: %zu \nlong is: %zu \nfloat is: %zu \ndouble is: %zu \nlong double is: %zu \n", sizeof(int), sizeof(short), sizeof(long), sizeof(float), sizeof(double), sizeof(long double));
}
// Chapter 7 page 158 question 10
void q3(void)
{
    printf("Enter a sentence: ");
    char letter = getchar();
    int number = 0;
    while (letter != '\n')
    {
        letter = toupper(letter);
        switch (letter)
        {
        case 'A':
        case 'E':
        case 'I':
        case 'O':
        case 'U':
            number++;
            break;
        default:
            break;
        }
        letter = getchar();
    }
    printf("Your sentence contains %d vowels. \n", number);
}
// Chapter 7 page 158 question 11
void q4(void)
{
    printf("Enter a first and last name: ");
    char letter = getchar();
    char fLetter = letter;
    while ((letter != '\n') && (letter != ' '))
    {
        letter = getchar();
    }
    letter = getchar();
    while (letter != '\n')
    {
        putchar(letter);
        letter = getchar();
    }
    printf(", %c. \n", fLetter);
}
// Chapter 7 page 159 question 13
void q5(void)
{
    printf("Enter a sentence: ");
    int spaces = 0;
    int length = 0;
    int letter = getchar();
    while (letter != '\n')
    {
        length++;
        if (letter == ' ')
        {
            spaces++;
        }
        letter = getchar();
    }
    printf("Average word length: %.1f \n", ((float)length - spaces) / (spaces + 1));
}
// Chapter 7 page 157 question 4
void q6(void)
{
    printf("Enter a phone number: ");
    char letter = getchar();
    while (letter != '\n')
    {
        letter = toupper(letter);
        switch (letter)
        {
        case 'A':
        case 'B':
        case 'C':
            printf("2");
            break;
        case 'D':
        case 'E':
        case 'F':
            printf("3");
            break;
        case 'G':
        case 'H':
        case 'I':
            printf("4");
            break;
        case 'J':
        case 'K':
        case 'L':
            printf("5");
            break;
        case 'M':
        case 'N':
        case 'O':
            printf("6");
            break;
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
            printf("7");
            break;
        case 'T':
        case 'U':
        case 'V':
            printf("8");
            break;
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
            printf("9");
            break;
        case '+':
            printf("0");
            break;
        default:
            printf("Error - need to enter a letter or + \n");
            break;
        }
        letter = getchar();
    }
}
int main(void)
{
    //q1();
    //q2();
    //q3();
    //q4();
    //q5();
    q6();
    system("pause");
    return 0;
}