#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>

struct testStruct
{
    int order;
    int info;
};
int compareFunc(const void *p1, const void *p2)
{
    int *a = (int *)p1;
    int *b = (int *)p2;
    return *a - *b;
}
int compareFuncStruct(const void *p1, const void *p2)
{
    testStruct *a = (testStruct *)p1;
    testStruct *b = (testStruct *)p2;
    return a->order - b->order;
}
void myQ_Sort(void *toSort, size_t sizeOfElement, int numOfElements, int (*compareFunc)(const void *p1, const void *p2))
{
    if (toSort == NULL || numOfElements == 0)
        return;
    void *comparePtr = (void *)malloc(sizeOfElement);
    memcpy(comparePtr, toSort, sizeOfElement);
    void *low = toSort;
    void *hole = toSort;
    void *high = (char *)toSort + (sizeOfElement * (numOfElements - 1));
    while (low != high)
    {
        if (low == hole)
        {
            if (compareFunc(high, comparePtr) + 1 > 0) //same or greater
                high = (char *)high - sizeOfElement;
            else
            {
                memcpy(hole, high, sizeOfElement);
                hole = high;
                low = (char *)low + sizeOfElement;
            }
        }
        else
        {
            if (compareFunc(comparePtr, low) + 1 > 0) //same or greater
                low = (char *)low + sizeOfElement;
            else
            {
                memcpy(hole, low, sizeOfElement);
                hole = low;
            }
        }
    }
    memcpy(low, comparePtr, sizeOfElement);
    free(comparePtr);
    if (numOfElements <= 2)
        return;
    myQ_Sort(toSort, sizeOfElement, ((char *)low - (char *)toSort) / sizeOfElement, compareFunc);                                             //sort the small side
    myQ_Sort((char *)high + sizeOfElement, sizeOfElement, numOfElements - (((char *)low - (char *)toSort) / sizeOfElement) - 1, compareFunc); //sort the small side
}

void test(void)
{
#define type int
#define WAY_TO_PRINT "%d %d\n"
#define compareFunction compareFunc
#define sizeOfArray 100000
    type x[sizeOfArray];
    srand(0);
    for (int i = 0; i < sizeOfArray; i++)
        x[i] = rand() % 0xffff;
    myQ_Sort(x, sizeof(type), sizeOfArray, compareFunction);
    int i;
    for (i = 1; i < sizeOfArray; i++)
        //printf(WAY_TO_PRINT, x[i].order, x[i].info);
        if (x[i] < x[i - 1])
            break;
    if (i != sizeOfArray)
        printf("%d", i);
    else
        printf("good");
}
int main(void)
{
    test();
    system("pause");
    return 0;
}