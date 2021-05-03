//Things were compiled differently due to file name change
#include <stdio.h>
#include <stdlib.h>
#include "linkList.h"
//#include <math.h>
//#include <stdbool.h>
//#include <complex.h>
//#include <ctype.h>
//#include <time.h>
#include <string.h>
//#include <stdarg.h>
//#include <assert.h>

#ifdef _WIN32
#define printRed 0
#define printReset 0
#else
#define printRed printf("\033[01;31m")
#define printReset printf("\033[0m;")
#endif // _WIN32

typedef unsigned char uByte;
typedef unsigned short preMap;
typedef unsigned long tileNum;
#define DEFAULT_DIMENSION 100
tileNum numOfRows = 3;
tileNum numOfCols = 6;
unsigned long long numOfSquares;
preMap *givenGrid;
enum bits
{
    per = 1 << 5,
    N = 1 << 4,
    E = 1 << 3,
    S = 1 << 2,
    W = 1 << 1,
    vis = 1
};
uByte *newGrid;
void getGrid(FILE *fp) //premap
{
    givenGrid = (preMap *)calloc(numOfSquares, sizeof(preMap));
    tileNum curr = 0;
    while (fgetc(fp) != '\n') //top line (top most wall)
    {
        if (fgetc(fp) == '_')
            givenGrid[curr] += 16;
        curr++;
    }
    for (tileNum i = 0; i < numOfRows; i++) //go through the rest
    {
        if (fgetc(fp) == '|')
            givenGrid[i * numOfCols] += 2;
        for (tileNum j = 0; j < numOfCols; j++) //person + left, right walls
        {
            if (fgetc(fp) == 'X')
                givenGrid[i * numOfCols + j] += 32;
            if (fgetc(fp) == '|')
            {
                givenGrid[i * numOfCols + j] += 8;
                if (j + 1 != numOfCols)
                    givenGrid[i * numOfCols + j + 1] += 2;
            }
        }
        fgetc(fp);                                 // it is a newLine
        for (tileNum j = 0; fgetc(fp) == ' '; j++) //the top and bottem walls
        {
            if (fgetc(fp) == '_')
            {
                givenGrid[i * numOfCols + j] += 4;
                if (i + 1 != numOfRows)
                    givenGrid[(i + 1) * numOfCols + j] += 16;
            }
        }
    }
}
bool notDone()
{
    for (tileNum i = 0; i < numOfRows; i++)
        for (tileNum j = 0; j < numOfCols; j++)
            if (newGrid[i * numOfCols + j] % 2 == 0)
                return 1;
    return 0;
}
tileNum moveTo(tileNum direction, tileNum currLoc)
{
    if (givenGrid[currLoc] & direction)
        return -1;
    else if (direction & S)
        return currLoc + numOfCols;
    else if (direction & E)
        return currLoc + 1;
    else if (direction & N)
        return currLoc - numOfCols;
    return currLoc - 1;
}
tileNum BFS(tileNum currNum, tileNum *path)
{
    uByte i;
    tileNum newNum;
    queue *toGo = NULL;
    while (newGrid[currNum] & vis)
    {
        for (i = 0; i < 4; i++)
        {
            newNum = moveTo(1 << (i + 1), currNum);
            if (newNum != -1)
            {
                toGo = enque(toGo, newNum);
                if (path[newNum] == 0)
                    path[newNum] = currNum + 1;
            }
        }
        currNum = deque(&toGo);
    }
    while (toGo != NULL)
        deque(&toGo);
    return currNum;
}
queue *addRoute(tileNum loc, tileNum *BFS_path, queue *startPath, tileNum callLoc)
{
    if (loc != callLoc)
    {
        startPath = addRoute(BFS_path[loc] - 1, BFS_path, startPath, callLoc);
        startPath = enque(startPath, loc);
    }
    return startPath;
}
uByte walls(tileNum loc)
{
    return (givenGrid[loc] & N) | (givenGrid[loc] & E) | (givenGrid[loc] & S) | (givenGrid[loc] & W);
}
uByte person(tileNum loc)
{
    return givenGrid[loc] & per;
}
queue *printGrid(queue *curr)
{
    //if theres is a victem -> print red
    while (curr->next != NULL)
    { //set it
        if (curr->next->storage > curr->storage)
            if (curr->next->storage - 1 == curr->storage)
                givenGrid[curr->storage] = (givenGrid[curr->storage] % 256) | ('>' << 8);
            else
                givenGrid[curr->storage] = (givenGrid[curr->storage] % 256) | ('v' << 8);
        else if (curr->next->storage + 1 == curr->storage)
            givenGrid[curr->storage] = (givenGrid[curr->storage] % 256) | ('<' << 8);
        else
            givenGrid[curr->storage] = (givenGrid[curr->storage] % 256) | ('^' << 8);
        curr = curr->next;
    }
    givenGrid[curr->storage] = (givenGrid[curr->storage] % 256) | ('X' << 8);
    tileNum j;
    for (j = 0; j < numOfCols; j++)
    { //top line (top most wall)
        putc(' ', stdout);
        if (givenGrid[j] & N)
            putc('_', stdout);
        else
            putc(' ', stdout);
    }
    putc('\n', stdout);
    for (tileNum i = 0; i < numOfRows; i++)
    { //go through the rest
        if (givenGrid[i * numOfCols] & W)
            putc('|', stdout);
        else
            putc(' ', stdout);
        for (j = 0; j < numOfCols; j++)
        { //person + left, right walls
            if (givenGrid[i * numOfCols + j] >> 8)
            { //something to put there
                if (givenGrid[i * numOfCols + j] & per)
                {
                    printRed;
                    printf("%c", givenGrid[i * numOfCols + j] >> 8);
                    printReset;
                }
                else
                    putc(givenGrid[i * numOfCols + j] >> 8, stdout);
                givenGrid[i * numOfCols + j] = (givenGrid[i * numOfCols + j] % 256) | ('.' << 8);
            }
            else
                putc(' ', stdout);
            if (givenGrid[i * numOfCols + j] & E)
                putc('|', stdout);
            else
                putc(' ', stdout);
        }
        putc('\n', stdout);
        for (j = 0; j < numOfCols; j++)
        { //the top and bottem walls
            putc(' ', stdout);
            if (givenGrid[i * numOfCols + j] & S)
                putc('_', stdout);
            else
                putc(' ', stdout);
        }
        putc('\n', stdout);
    }
    return curr;
}
int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("MAIN: User Failier -> grid has not been given\n");
        exit(EXIT_FAILURE);
    }
    //get the rows and cols
    numOfRows = DEFAULT_DIMENSION;
    numOfCols = DEFAULT_DIMENSION;
    tileNum *location;
    for (int i = 2; i < argc; i++)
    {
        if (argv[i][1] == 'r')
            location = &numOfRows;
        else if (argv[i][1] == 'c')
            location = &numOfCols;
        else
            continue;
        *location = 0;
        for (int j = 2; argv[i][j] != '\0'; j++)
            *location = *location * 10 + argv[i][j] - '0';
    }
    numOfSquares = numOfCols * numOfRows;
    //printf("%d", numOfSquares);
    newGrid = (uByte *)malloc(numOfSquares * sizeof(uByte));
    memset(newGrid, 0, numOfSquares * sizeof(uByte));
    queue *journey = (queue *)malloc(sizeof(queue));
    journey->next = NULL;
    journey->storage = 0;
    queue *curr = journey;
    FILE *fp = NULL;
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("MAIN: User failier -> invalid grid location!!!\n");
        exit(EXIT_FAILURE);
    }
    getGrid(fp);
    fclose(fp);
    tileNum *path = (tileNum *)calloc(numOfSquares, sizeof(tileNum));
    uByte i = 0;
    tileNum currLoc = 0;
    tileNum testLoc = 0;
    printGrid(curr);
    newGrid[testLoc] = walls(testLoc) | person(testLoc) | vis;
    while (notDone())
    {
        printf("press enter to continue: ");
        while (getchar() != '\n')
            ;
        for (i = 0; i < 4; i++)
        { //find a dir I can go
            testLoc = moveTo(N >> i, currLoc);
            if ((testLoc != -1) && (!(newGrid[testLoc] & vis)))
            {
                journey = enque(journey, testLoc);
                break;
            }
        }
        if (i == 4)
        { //stuck
            testLoc = BFS(currLoc, path);
            journey = addRoute(testLoc, path, journey, currLoc);
            memset(path, 0, sizeof(tileNum) * numOfSquares);
        }
        newGrid[testLoc] = walls(testLoc) | person(testLoc) | vis;
        currLoc = testLoc;
        curr = printGrid(curr);
    }
    printf("Now going back home:\npress enter to continue: ");
    while (getchar() != '\n')
        ;
    newGrid[0] = newGrid[0] & (~vis);
    testLoc = BFS(currLoc, path);
    journey = addRoute(testLoc, path, journey, currLoc);
    curr = printGrid(curr);
    //system("pause");
    return 0;
}