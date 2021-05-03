#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Chapter 5 page 96 number 2
void q1(void)
{
    int hours, mins;
    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &hours, &mins);

    if (hours >= 24 || hours <= 0)
    {
        printf("Error non-valid input");
    }
    else if (hours > 12)
    {
        hours -= 12;
        printf("Equivalent 12-hour time: %d:%d PM \n", hours, mins);
    }
    else
    {
        printf("Equivelent 12-hour time: %d:%d AM \n", hours, mins);
    }
}

// Chapter 5 page 96 number 5
void q2(void)
{
    float income;
    printf("Enter your income: ");
    scanf("$%f", &income);
    if (income <= 750)
    {
        printf(" You tax due is: $%.2f \n", income * 0.01);
    }
    else if ((income > 750) && (income <= 2500))
    {
        printf(" You tax due is: $%.2f \n", ((income - 750) * 0.02) + 7.50);
    }
    else if ((income > 2250) && (income <= 3750))
    {
        printf(" You tax due is: $%.2f \n", ((income - 2250) * 0.03) + 37.50);
    }
    else if ((income > 3750) && (income <= 5250))
    {
        printf(" You tax due is: $%.2f \n", ((income - 3750) * 0.04) + 82.50);
    }
    else if ((income > 5250) && (income <= 7000))
    {
        printf(" You tax due is: $%.2f \n", ((income - 5250) * 0.05) + 142.50);
    }
    else
    {
        printf(" You tax due is: $%.2f \n", ((income - 7000) * 0.06) + 230.00);
    }
}

// Chapter 5 page 96 number 7
void q3(void)
{
    int first, second, third, fourth, least1, greatest1, least2, greatest2, greatestAll, leastAll;
    printf("Enter four integers: ");
    scanf("%d %d %d %d", &first, &second, &third, &fourth);
    if (first >= second)
    {
        greatest1 = first;
        least1 = second;
    }
    else
    {
        greatest1 = second;
        least1 = first;
    }
    if (fourth <= third)
    {
        greatest2 = fourth;
        least2 = third;
    }
    else
    {
        greatest2 = third;
        least2 = fourth;
    }
    if (greatest1 < greatest2)
    {
        greatestAll = greatest2;
    }
    else
    {
        greatestAll = greatest1;
    }
    if (least1 > least2)
    {
        leastAll = least2;
    }
    else
    {
        leastAll = least1;
    }
    printf("Smallest: %d \n", leastAll);
    printf("Largest: %d \n", greatestAll);
}

// Chapter 5 page 96 number 10
void q4(void)
{
    int grade, tens;
    printf("Enter numerical grade:");
    scanf("%d", &grade);
    tens = grade / 10;
    switch (tens)
    {
    case 10:
    case 9:
        printf("Letter grade: A");
        break;
    case 8:
        printf("Letter grade: B");
        break;
    case 7:
        printf("Letter grade: C");
        break;
    case 6:
        printf("Letter grade: D");
        break;
    case 5:
    case 4:
    case 3:
    case 2:
    case 1:
    case 0:
        printf("Letter grade: F");
        break;
    default:
        printf("ERROR INVALID GRADE! DOUBLE CHECK!");
        break;
    }
}

// chapter 6 page 122 number 1
void q5(void)
{
    float number, greatest;
    greatest = 0;
    do
    {
        printf("Enter a number: ");
        scanf("%g", &number);
        if (number > greatest)
        {
            greatest = number;
        }
        else if (greatest == 0)
        {
            greatest = number;
        }
    } while (number > 0);
    printf("The largest number entered was %g \n", greatest);
}

// chapter 6 page 122 number 2
void q6(void)
{
    int first, second;
    printf("Enter two integers: ");
    scanf("%d %d", &first, &second);
    int least = first > second ? second : first;
    int greatest = first > second ? first : second;
    int GCD = 0;
    int remainder = 1;
    for (; remainder != 0;)
    {
        remainder = greatest % least;
        greatest = least;
        least = remainder;
    }
    GCD = least;
    printf("Greatest common divisor: %d \n", GCD);
}

// chapter 6 page 123 number 3
void q7(void)
{
    int first, second;
    printf("Enter a fraction: ");
    scanf("%d/%d", &first, &second);
    int least = first > second ? second : first;
    int greatest = first > second ? first : second;
    int GCD = 0;
    int remainder = 1;
    for (; remainder != 0;)
    {
        remainder = greatest % least;
        greatest = least;
        least = remainder;
    }
    GCD = least;
    printf("In lowest terms: %d/%d \n", first / GCD, second / GCD);
}

// chapter 6 page 123 number 6
void q8(void)
{
    int n, i;
    printf("Enter a number: ");
    scanf("%d", &i);
    printf("The even squares between 1 and %d are/is: \n", i);
    for (n = 2; (n * n) <= i; n += 2)
    {
        printf("%d \n", n * n);
    }
}

// chapter 6 page 123 number 8
void q9(void)
{
    int numberdays, i;
    printf("Enter number of days in month: ");
    scanf("%d", &numberdays);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &i);
    for (int soFar = (2 - i); soFar <= numberdays; soFar++)
    {
        if (soFar <= 0)
        {
            printf("   ");
        }
        else if ((soFar + i - 2) % 7 == 0)
        {
            //the first column has no leading spaces
            printf("\n%3d", soFar);
        }
        else
        {
            printf("%3d", soFar);
        }
    }
    printf("\n");
}

void q9b(void)
{
    int numberDays, startDay, count = 0, i = 0;
    printf("Enter number of days in month: ");
    scanf("%d", &numberDays);
    printf("Enter starting day of the week (1=Sun, 7=Sat): ");
    scanf("%d", &startDay);

    for (i = 1; i < startDay; i++)
    {
        printf("   ");
        count++;
    }

    for (i = 1; i <= numberDays; i++)
    {
        printf("%3d", i);
        count++;
        if (count % 7 == 0)
            printf("\n");
    }
}

// chapter 6 page 123 number 11
void q10(void)
{
    int upTo;
    printf("Enter a number: ");
    scanf("%d", &upTo);
    float sum = 1.0;
    float x = 1.0;
    for (int i = 1; i <= upTo; i++)
    {
        x *= i;
        sum += 1 / x;
    }
    printf("\n%f", sum);
}

int main(void)
{
    // q1();
    // q2();
    // q3();
    // q4();
    // q5();
    // q6();
    // q7();
    // q8();
    // q9();
    // q9b();
    // q10();
    system("pause");
    return (0);
}