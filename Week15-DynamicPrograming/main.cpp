#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <complex.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
long long fibArray[100] = {0, 1};
int fibonacci(int n)
{
    if ((!fibArray[n]) && (n != 0))
        fibArray[n] = fibonacci(n - 2) + fibonacci(n - 1);
    return fibArray[n];
}

int *numOfPaths;

int readNumInFile(FILE **fp)
{
    char ch = fgetc(*fp);
    int num = 0;
    while ((ch != '\n') && (ch != ' '))
    {
        num = num * 10 + ch - '0';
        ch = fgetc(*fp);
    }
    return num;
}

int findNumOfPaths(int *inputArray, int rowNum, int colNum, int rows, int cols)
{
    if (numOfPaths[(rowNum * cols) + colNum])
        return numOfPaths[(rowNum * cols) + colNum] - 1; //because i want to easily be able to check weather I went through this prosess
    int collectiveTotal = 0;
    int currentNum = inputArray[(rowNum * cols) + colNum];
    for (int i = rowNum + 1; i < rows; i++)
    {
        for (int j = colNum + 1; j < cols; j++)
        {
            if (inputArray[(i * cols) + j] != currentNum)
            {
                collectiveTotal += findNumOfPaths(inputArray, i, j, rows, cols);
                collectiveTotal %= 1000000007;
            }
        }
    }
    numOfPaths[(rowNum * cols) + colNum] = collectiveTotal + 1;
    return collectiveTotal;
}

void silverHopscotchFeb2015(const char *filein, const char *fileout)
{
    FILE *fpIn = NULL;
    //fopen_s(&fpIn, filein, "r");
    fpIn = fopen(filein, "r");
    int rows = readNumInFile(&fpIn);
    int cols = readNumInFile(&fpIn);
    int maxNum = readNumInFile(&fpIn);
    numOfPaths = (int *)malloc(sizeof(int) * cols * rows);
    memset(numOfPaths, 0, sizeof(int) * cols * rows);
    numOfPaths[(rows * cols) - 1] = 2;
    int *inputArray = (int *)malloc(sizeof(int) * cols * rows);
    int arraySize = cols * rows;
    for (int i = 0; i < arraySize; i++)
        inputArray[i] = readNumInFile(&fpIn);
    fclose(fpIn);
    FILE *fpOut = NULL;
    //fopen_s(&fpOut, fileout, "w");
    fpOut = fopen(fileout, "w");
    fprintf(fpOut, "%d", findNumOfPaths(inputArray, 0, 0, rows, cols));
    fclose(fpOut);
}
int main(void)
{
    //silverHopscotchFeb2015("./Debug/hopscotch.in", "./Debug/hopscotch.out"); //mistake: didn't mod inside of the loop so it got bigger and bigger and did messed up things
    silverHopscotchFeb2015("hopscotch.in", "hopscotch.out");
    printf("%d", fibonacci(10));
    system("pause");
    return 0;
}