#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>

// Chapter 11 page 255 number 1
//Aliases wiht pointers
// Answer: a, g, h

//Chapter 11 page 255 number 2
//answer none

//chapter 11 page 255 number 3
//debuging
/*void avg_sum(double a[], int n, double *avg, double *sum)
{
	int i;
	*sum = 0.0;
	for (i = 0; i < n; i++)
		*sum += a[i]
	*avg = *sum / n
}*/

//chapter 11 page 255 number 4
//exchange values
void q1(int *p, int *q)
{
	int x = *p;
	*p = *q;
	*q = x;
}

//chapter 11 page 255 number 5
// split up time into hours miutes and seconds
void q2(long totalTime, int *h, int *m, int *s)
{
	*h = totalTime / 3600;
	totalTime -= *h * 3600;
	*m = totalTime / 60;
	totalTime -= *m * 60;
	*s = totalTime;
}

//chapter 11 page 255 number 6
// find the first and second biggest numbers in a list [a] with length n
void q3(int a[], int n, int *largest, int *secondLargest)
{
	if (a[1] > a[0])
	{
		*largest = a[1];
		*secondLargest = a[0];
	}
	else
	{
		*largest = a[0];
		*secondLargest = a[1];
	}
	for (int i = 2; i < n; i++)
	{
		if (a[i] > *largest)
		{
			*secondLargest = *largest;
			*largest = a[i];
			continue;
		}
		if (a[i] > *secondLargest)
		{
			*secondLargest = a[i];
		}
	}
}

//chapter 11 page 256 number 7
//find the month and day of a input year
void q4(int dayOfYear, int year, int *month, int *day)
{
	int i = 0;
	*month = 1;
	int Months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (year % 4 == 0)
	{
		Months[1]++;
	}
	if (dayOfYear - Months[i]> 0)
	{
		*month = *month + 1;
		dayOfYear -= Months[i];
		i++;
	}
	*day = dayOfYear;
}

//chapter 11 page 256 number 8
//go in an array and return a pointer to the arrays largest elemanet
int *q5(int a[], int n)
{
	int *largest = a;
	for (int i = 1; i < n; i++)
	{
		if (a[i] > *largest)
		{
			*largest = a[i];
		}
	}
	return largest;
}
int main(void)
{
	/*int i = 0, j = 1;
	q1(&i, &j);
	printf("%d%d\n", i, j);*/
	/*int hours, minutes, seconds;
	q2(3661, &hours, &minutes, &seconds);
	printf("%d %d %d\n", hours, minutes, seconds);*/
	/*int n = 6, a[6] = { 7,9,10,3,0,-1 }, large, secLarge;
	q3(a, n, &large, &secLarge);
	printf("%d %d\n", large, secLarge);*/
	int month, day;
	q4(32, 2001, &month, &day);
	printf("%d %d\n", month, day);
	/*const int n = 6;
	int a[n] = {0,1,2,3,4,5};
	int *p = q5(a, n);
	printf("%d\n", *p);*/
	system("pause");
	return 0;
}