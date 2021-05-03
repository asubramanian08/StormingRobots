#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Chapter 2 Page 34 Question 1
void q1(void)
{
    printf("       *\n      *\n     *\n*   *\n * *\n  *\n");
}

// Chapter 2 Page 34 Question 4
int q2(void)
{
    float money;
    printf("Enter an amount:");
    scanf("%f", &money);
    float taxMoney = money * 1.05;
    printf("With tax added: %.2f\n", taxMoney);
    return 0;
}

// Chapter 2 Page 34 Question 7
void q3(void)
{
    int amount;
    printf("Enter a dollar amount: ");
    scanf("%d", &amount);

    int twenties = amount / 20;
    amount -= twenties * 20;
    printf("\n$20 bills: %d", twenties);

    int tens = amount / 10;
    amount -= tens * 10;
    printf("\n$10 bills: %d", tens);

    int fives = amount / 5;
    amount -= fives * 5;
    printf("\n$5 bills: %d", fives);

    printf("\n$1 bills: %d \n", amount);
}

// Chapter 2 Page 34 Question 8
void q4(void)
{
    float startLoan;
    printf("Enter amount of loan:");
    scanf("%f", &startLoan);
    float interestRate;
    printf("Enter interest rate:");
    scanf("%f", &interestRate);
    float monthlyRate = (interestRate / 1200) + 1;
    float monthlyPayment;
    printf("Enter monthly payment:");
    scanf("%f", &monthlyPayment);
    float first = (monthlyRate * startLoan) - monthlyPayment;
    float second = (first * monthlyRate) - monthlyPayment;
    float third = (second * monthlyRate) - monthlyPayment;
    printf("Balance remaining after first payment: %.2f \n Balance remaining after second payment: %.2f \n Balance remaining after third payment: %.2f \n", first, second, third);
}

// Chapter 3 Page 50 Question 1
void q5(void)
{
    int day, month, year;
    printf("Enter a date (mm/dd/yyyy) : ");
    scanf("%d/%d/%d", &month, &day, &year);
    printf("You entered the date %.4d%.2d%.2d \n", year, month, day);
}

// Chapter 3 Page 50 Question 2
void q6(void)
{
    int item;
    float price;
    int month, day, year;
    printf("Enter item number: ");
    scanf("%d", &item);
    printf("Enter unit price: ");
    scanf("%f", &price);
    printf("Enter purchase date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &month, &day, &year);
    printf(" \nItem\t\tUnit\t\tPurchase \n\t\tPrice\t\tDate \n%d\t\t$  %.2f\t\t%d/%d/%d \n", item, price, month, day, year);
}

// Chapter 3 Page 50 Question 3
void q7(void)
{
    int identifier, GS1, code, number, digit;
    printf("Enter ISBN:");
    scanf("%d-%d-%d-%d-%d", &GS1, &identifier, &code, &number, &digit);
    printf("GS1 prefix: %d", GS1);
    printf("Group identifier: %d", identifier);
    printf("Publisher code: %d", code);
    printf("Item number: %d", number);
    printf("Check digit: %d", digit);
}

// Chapter 3 Page 50 Question 4
void q8(void)
{
    int first, second, third;
    printf("Enter phone number [(xxx) xxx-xxxx] : ");
    scanf("(%d) %d-%d", &first, &second, &third);
    printf("You entered %3.3d.%3.3d.%4.4d\n", first, second, third);
}

// Chapter 4 Page 71 Question 1
void q9(void)
{
    int big;
    printf("Enter a two-digit number: ");
    scanf("%d", &big);
    int second = big % 10;
    int first = big / 10;
    printf("The reversal is: %d%d \n", second, first);
}

// Chapter 4 Page 71 Question 2
void q10(void)
{
    int big;
    printf("Enter a two/three-digit number: ");
    scanf("%d", &big);
    int third = big % 10;
    int second = (big / 10) % 10;
    int first = big / 100;
    if (first == 0)
        printf("The reversal is %d%d \n", third, second);
    else
        printf("The reversal is %d%d%d \n", third, second, first);
}

// Chapter 4 Page 71 Question 4
void q11(void)
{
    int first, second, third, fourth, fifth, base10;
    printf("Enter a number between 0 and 32767: ");
    scanf("%d", &base10);
    first = base10 / 4096;
    second = (base10 - (first * 4096)) / 512;
    third = (base10 - (first * 4096) - (second * 512)) / 64;
    fourth = (base10 - (first * 4096) - (second * 512) - (third * 64)) / 8;
    fifth = base10 - (first * 4096) - (second * 512) - (third * 64) - (fourth * 8);
    printf("In octal, your number is : %d%d%d%d%d \n", first, second, third, fourth, fifth);
}

// Chapter 4 Page 71 Question 4 another way of solving
void q11b(void)
{
    int base10;
    printf("Enter a number between 0 and 32767: ");
    scanf("%d", &base10);
    int first = base10 % 8;
    base10 = base10 / 8;
    int second = base10 % 8;
    base10 = base10 / 8;
    int third = base10 % 8;
    base10 = base10 / 8;
    int fourth = base10 % 8;
    base10 = base10 / 8;
    int fifth = base10 % 8;
    printf("In octal, your number is : %d%d%d%d%d \n", fifth, fourth, third, second, first);
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
    // q10();
    // q11();
    // q11b();
    system("pause");
    return (0);
}