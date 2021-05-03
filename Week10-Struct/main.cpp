#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>

//chapter 12 page 273 number 3
//what will happen? Answer - the list's value will repeater 1, 10, 1, 10 and continued

//chapter 12 page 273 number 5
// (a) and (d) are illegal

//chapter 12 page 275 number 17
//Rewrite a program to find the sum of an array
int q1(int *a, int n, int len)
{
    int sum = 0;
    int i = 0;
    int numOfItemsInArray = n * len;
    while (i < numOfItemsInArray)
    {
        sum += *a;
        i++;
        a++;
    }
    return sum;
}

//chapter 12 page 275 number 1
//print reversal
void q2(void)
{
    printf("Enter a phrase that you want reversed: ");
    char input[100];
    char *p = &input[0];
    char ch = getchar();
    while (ch != '\n')
    {
        *p = ch;
        p++;
        ch = getchar();
    }
    for (p--; p >= &input[0]; p--)
    {
        printf("%c\n", *p);
    }
}

//chapter 12 page 275 number 2
//Check if a sentence is a palendrome
void q3(void)
{
    printf("Enter a message: ");
    int i = 0;
    char ch = getchar();
    char input[100] = {}; // this contains only letters
    while (ch != '\n')
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            ch = towlower(ch);
        }
        if (ch < 'a' || ch > 'z')
        {
            ch = getchar();
            continue;
        }
        input[i] = ch;
        i++;
        ch = getchar();
    }
    char *end = &input[i - 1], *start = &input[0];
    for (; end > start; end--, start++)
    {
        if (*end != *start)
        {
            break;
        }
    }
    if (start < end)
    {
        printf("Not a palindrome\n");
    }
    else
    {
        printf("Palindrome\n");
    }
}

//online question 1 from basics in struct
//the diffence between two things
//in A. the Point is a type, but in B. the P is variable of type {double x, double y}

//online question 2 from basics in struct
//debuging code
//POINT is a variable not a type so 'POINT a;' does not work because that is just two undefiend variables next to eachother

//online question 3 from basics in struct
/*struct POINT{double x; double y;} test;
const POINT a;
test.x = .25; test.y = .75;*/

//online question 4 from basics in struct
//find the distance between two point
struct point
{
    double x;
    double y;
};
float q4(point p1, point p2)
{
    float distance = sqrt(((p1.x - p2.x) * (p1.x - p2.x)) + ((p1.y - p2.y) * (p1.y - p2.y))); // X2 + Y2 = z
    return distance;
}

//online question 5 from basics in struct
// return 1 if point are equal and 0 if else
int q5(point p1, point p2)
{
    if (q4(p1, p2) > 0.00001 || q4(p1, p2) < -0.00001)
    {
        return 0;
    }
    return 1;
}

//online question 6 from basics in struct
//find the area of a rectangle
struct rect
{
    point p1;
    point p2;
};
double q6(rect r)
{
    return (r.p2.x - r.p1.x) * (r.p1.y - r.p2.y);
}

//online question 7 from basics in struct
// is a point in a rectangle 1 if yes and 0 if no
int q7(rect r, point p)
{
    if ((p.x >= r.p1.x && p.x <= r.p2.x) && (p.y <= r.p1.y && p.y >= r.p2.y))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//online question 8 from basics in struct
// is a rectangle inside another
int q8(rect r1, rect r2)
{
    if (q7(r1, r2.p1) && q7(r1, r2.p2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//online question 9 from basics in struct
//find which rectange has a bigger area
void q9(rect r1, rect r2)
{
    if (q6(r1) > q6(r2))
    {
        printf("r1\n");
    }
    else
    {
        printf("r2\n");
    }
}

//online question 10 from basics in struct
//giving 5 points find the pair that is the farthest away
void q10(point a[])
{
    rect farthest = {a[0], a[1]};
    float dist = q4(a[0], a[1]);
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (q4(a[i], a[j]) > dist)
            {
                farthest = {a[i], a[j]};
                dist = q4(a[i], a[j]);
            }
        }
    }
    printf("%f is the distance between %g,%g and %g,%g\n", dist, farthest.p1.x, farthest.p1.y, farthest.p2.x, farthest.p2.y);
}
int main(void)
{
    /*const int LEN = 4;
	const int n = 3;
	const int a[n][LEN] = {
		{0,0,2,3},
		{1,2,3,5},
		{0,7,1,1} };
	printf("%d\n",q1((int *)a, n, LEN));*/
    //q2();
    //q3();
    /*point p1 = { 10,6.63324958 };
	point p2 = { 0,0 };
	printf("%g\n",q4(p1, p2));*/
    /*point p1 = { 2,3 }, p2 = { 2,3.000011};
	printf("%d\n", q5(p1, p2));*/
    /*rect r = { {3,4},{6,1} };
	printf("Area: %.3f", q6(r));*/
    /*rect r = { {3,4},{6,1} };
	point p = { 4,4 };
	printf("%d\n", q7(r,p));*/
    /*rect r1 = { {3,4},{6,1} };
	rect r2 = { {4,3},{5,0} };
	printf("%d\n", q8(r1, r2));*/
    /*rect r1 = { {3,4},{6,1} };
	rect r2 = { {3,4},{6,0} };
	q9(r1, r2);*/
    /*point a[5] = { {0,0},{1,1},{2,2},{3,3},{4,4} };
	q10(a);*/
    system("pause");
    return 0;
}