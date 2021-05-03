#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
int add(int a, int b)
{
    int carryOver = a & b;
    if (!carryOver)
        return a | b;
    else
        return add(carryOver << 1, a ^ b);
}
/*int subtract2(int a, int b)
{
	int borrow = (~a) & b;
	if (!borrow)
		return a ^ b;
	else
		subtract2(a ^ b, borrow << 1);
}*/
int subtract(int a, int b)
{
    return add(a, add(~b, 1)); //a and -b
}
/*int multiply2(int a, int b)
{
	int bitsInInt = sizeof(int) * 8;
	int product = 0;
	for (int i = 0; i < bitsInInt; i++)
	{
		if (a & 1 << i)
			product = add(product, b << i);
	}
	return product;
}*/
int multiply(int a, int b)
{
    int addLater = 0;
    while (b != 1)
    {
        if (b & 0x0001)
            addLater = add(addLater, a);
        b >>= 1;
        a <<= 1;
    }
    return add(a, addLater);
}
/*int divide2(int a, int b)
{
	int quotent = 0;
	int newDividend = a;
	int shift;
	for (shift = 0; (b << shift) <= a; shift++);
	for (shift--; shift >= 0; shift--)
	{
		if (b << shift <= newDividend)
		{
			newDividend = subtract(newDividend, b << shift);
			quotent = (quotent << 1) | 1;
		}
		else
			quotent <<= 1;
	}
	return quotent;
}*/
int divide(int a, int b)
{
    if (a < b)
        return 0;

    int shiftNum = 0;
    for (shiftNum; a >= (b << 1) /*i would be counting one extra for b to be > a*/; shiftNum++)
        b <<= 1;
    return add(1 << shiftNum, divide(subtract(a, b), b >> shiftNum));
}
/*int mod1(int a, int b)
{
	int newDividend = a;
	int shift;
	for (shift = 0; (b << shift) <= a; shift++);
	for (shift--; shift >= 0; shift--)
	{
		if (b << shift <= newDividend)
			newDividend = subtract(newDividend, b << shift);
	}
	return newDividend;
}*/
int mod(int a, int b)
{
    if (a < b)
        return a;
    int shiftNum = 0;
    for (shiftNum; a >= (b << 1) /*i would be counting one extra for b to be > a*/; shiftNum++)
        b <<= 1;
    return mod(subtract(a, b), b >> shiftNum);
}
int getNum(void)
{
    char ch = getchar();
    int num = 0;
    while (ch != '\n')
    {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num;
}
void parityBit(void)
{
    printf("Enter a number: ");
    char parityBit[][15] = {"odd parityBit", "even parityBit"};
    int num = getNum();
    bool bit1_0 = num & 1;
    bool toPlace = 0;
    printf("decimal: %d, hex: %x, bianary: ", num, num);
    for (int i = 32 /*numOf bits in int*/; i >= 0; i--)
    {
        if (num & 1 << i)
        {
            printf("1");
            toPlace = 1;
        }
        else if (toPlace)
            printf("0");
    }
    printf(" -- %s\n", parityBit[bit1_0]);
}

//question 3 was done above
void switchValues(int a, int b)
{
    a = a + b;
    b = a - b;
    a = a - b;
    printf("%d, %d\n", a, b);
    /*credit: Divya*/
}

struct myFloat
{

    unsigned int sign : 1;
    int exponent : 8;
    unsigned int fraction : 23;
};

void myFloatTest(void)
{
    myFloat a;
    a.sign = 0;
    a.fraction = 5;
    a.exponent = 2;

    float p = (float *)&a;
    float f = *p;
    printf("%f", f);
}
//question 6 - you make it an unsigned int
int main(void)
{
    printf("%d\n", mod(15, 5));
    system("pause");
    return 0;
}