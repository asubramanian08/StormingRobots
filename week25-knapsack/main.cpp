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

unsigned int *wt;
unsigned int *val;
unsigned long iterations = 0;
unsigned int cap;
unsigned int numOfItems;
unsigned int getNum()
{
    char ch;
    unsigned int total = 0;
    while ((ch = getchar()) != '\n')
        total = total * 10 + ch - '0';
    return total;
}
#define max_cap 10000000
#define max_item 10000000
#define __max(x, y) (x > y ? x : y)

//give the numberOf items + 1
unsigned int pureRecursive(unsigned int currItem, unsigned int capacity)
{
    if ((currItem == 0) || (capacity == 0))
        return 0;
    if (wt[currItem - 1] > capacity)
        return pureRecursive(currItem - 1, capacity);
    iterations++;
    return __max(val[currItem - 1] + pureRecursive(currItem - 1, capacity - wt[currItem - 1]), pureRecursive(currItem - 1, capacity));
}

//give the numberOf items + 1
unsigned int *memo; //[max_cap][max_item] = { 0 };
unsigned int memoizing(unsigned int currItem, unsigned int capacity)
{
    if ((currItem == 0) || (capacity == 0))
        return 0;
    currItem--;
    iterations++;
    if (!memo[capacity * numOfItems + currItem])
    {
        if (wt[currItem] > capacity)
            memo[capacity * numOfItems + currItem] = memoizing(currItem, capacity) + 1;
        else
            memo[capacity * numOfItems + currItem] = __max(val[currItem] + memoizing(currItem, capacity - wt[currItem]), memoizing(currItem, capacity)) + 1;
    }
    return memo[capacity * numOfItems + currItem] - 1;
}

unsigned int *cap_arr; //[max_item] [max_cap]
unsigned int knapsack_moreMem(unsigned int numOfItems, unsigned int capacity)
{
    memset(cap_arr, 0, sizeof(unsigned int) * capacity);
    for (unsigned int i = 1; i <= numOfItems; i++)
    {
        cap_arr[i * capacity + 0] = 0;
        for (unsigned int j = 0; j < capacity; j++)
        {
            if (j + 1 < wt[i - 1])
                cap_arr[i * capacity + j] = cap_arr[(i - 1) * capacity + j];
            else
                cap_arr[i * capacity + j] = __max(cap_arr[(i - 1) * capacity + j], val[i - 1] + cap_arr[(i - 1) * capacity + (j + 1 - wt[i - 1])]);
            iterations++;
        }
    }
    return cap_arr[numOfItems * capacity + (capacity - 1)];
}

unsigned int **knapsack_vals; //[2][max_cap]
unsigned int true_knapsack(unsigned int numOfItems, unsigned int capacity)
{
    unsigned int *curr = knapsack_vals[1];
    unsigned int *prev = knapsack_vals[0];
    unsigned int *temp;

    memset(prev, 0, capacity * sizeof(unsigned int));
    curr[0] = 0;
    for (unsigned int i = 0; i < numOfItems; i++)
    {
        for (unsigned int j = 0; j < capacity; j++)
        {
            if (j + 1 < wt[i])
                curr[j] = prev[j];
            else
                curr[j] = __max(prev[j], val[i] + prev[j + 1 - wt[i]]);
            iterations++;
        }
        temp = curr;
        curr = prev;
        prev = temp;
    }
    return prev[capacity - 1];
}

unsigned int (*knapsacks[])(unsigned int, unsigned int){pureRecursive, memoizing, knapsack_moreMem, true_knapsack};

int main(void)
{
    printf("Enter the number of times your would like to run knapsack. It will run with the same data. ");
    unsigned int numOfRuns = getNum();
    unsigned int *efficiency = (unsigned int *)malloc(sizeof(unsigned int) * numOfRuns);
    for (unsigned int i = 0; i < numOfRuns; i++)
    {
        printf("Enter the knapsack efficiency -> 0(least efficient) - 3(most efficient) for the %uth run: ", i + 1);
        while ((efficiency[i] = getNum()) > 3)
            printf("incorrect input\nEnter efficiency again: ");
    }
    printf("Enter the number of items: ");
    numOfItems = getNum();
    wt = (unsigned int *)calloc(numOfItems, sizeof(unsigned int));
    val = (unsigned int *)calloc(numOfItems, sizeof(unsigned int));
    printf("Enter the max capacity in bag: ");
    cap = getNum();

    //memoizing
    memo = (unsigned int *)calloc((cap + 1) * numOfItems, sizeof(unsigned int));
    //knapsack_moreMem
    cap_arr = (unsigned int *)malloc(sizeof(unsigned int) * (numOfItems + 1) * cap);
    //true_knapsack
    knapsack_vals = (unsigned int **)malloc(sizeof(unsigned int *) * 2);
    knapsack_vals[0] = (unsigned int *)malloc(sizeof(unsigned int) * cap);
    knapsack_vals[1] = (unsigned int *)malloc(sizeof(unsigned int) * cap);

    printf("Do you want computer generated values? 1/0: ");
    if (getNum() == 0) //computerGen
        for (unsigned int i = 0; i < numOfItems; i++)
        {
            printf("Enter the %dth weight: ", i + 1);
            wt[i] = getNum();
            printf("Enter the %dth value: ", i + 1);
            val[i] = getNum();
        }
    else
    { //manual input
        srand(0);
        printf("enter the max value of an item: ");
        unsigned int maxValue = getNum();
        for (unsigned int i = 0; i < numOfItems; i++)
        {
            wt[i] = rand() % cap;
            val[i] = rand() % maxValue;
        }
    }
    for (unsigned int timesRun = 0; timesRun < numOfRuns; timesRun++)
    { //run the knapsacks
        unsigned int maxVal = knapsacks[efficiency[timesRun]](numOfItems, cap);
        printf("Your knapsack efficiency of %d gave:\nThe maximum value is %u\nThe number of iterations is %lu\n", efficiency, maxVal, iterations);
        iterations = 0;
        if (efficiency[timesRun] == 1)                                //memoizing
            memset(memo, 0, cap * numOfItems * sizeof(unsigned int)); //reset everything
    }
    system("pause");
    return 0;
}