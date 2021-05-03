#include <stdio.h>
#include <stdlib.h>
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>
//#include <errno.h>
//#include <signal.h>
//#include <setjmp.h>
//_CRT_SECURE_NO_WARNINGS;

struct bitTree
{
    int *arr;
    unsigned long numOfItems;
    void startUp(unsigned long numOfElements)
    {
        numOfItems = numOfElements;
        arr = (int *)malloc(sizeof(int) * numOfElements);
        memset(arr, 0, sizeof(int) * numOfElements);
    }
    void update(int change, unsigned long element)
    {
        for (++element; element <= numOfItems; element += element & (~element + 1))
            arr[element - 1] += change;
    }
    long getSum(unsigned long element)
    {
        long sum = 0;
        for (++element; element; element &= element - 1)
            sum += arr[element - 1];
        return sum;
    }
    void finishTree(void)
    {
        free(arr);
    }
};
int main()
{
    bitTree myBitTree;
    unsigned int numOfElements = 10;
    myBitTree.startUp(numOfElements);
    myBitTree.update(20, 1);
    printf("%d", myBitTree.getSum(4));
    myBitTree.update(20, 5);
    myBitTree.update(20, 7);
    printf("%d", myBitTree.getSum(6));
    printf("%d", myBitTree.getSum(8));
    putc('\n', stdout);
    for (unsigned int i = 0; i < numOfElements; i++)
    {
        printf("%d\n", myBitTree.arr[i]);
    }
    system("pause");
    return 0;
}