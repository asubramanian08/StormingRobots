#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityQueue.h"

void *pQue = NULL;
void *endLoc;

#ifndef connectionMacros
#define connectionMacros true
#define getLeftChild(parent, pQue, sizeOfElement) ((((((char *)parent - (char *)pQue) / sizeOfElement) * 2) + 1) * sizeOfElement)
#define getRightChild(parent, pQue, sizeOfElement) (((((char *)parent - (char *)pQue) / sizeOfElement + 1) * 2) * sizeOfElement)
#define findParent(pQue, child, sizeOfElement) ((char *)pQue + ((((((char *)child - (char *)pQue) / sizeOfElement) - 1) / 2) * sizeOfElement))
#define correctChild(pQue, child, parent, sizeOfElement, compareFunc) (compareFunc(child = (char *)pQue + getLeftChild(parent, pQue, sizeOfElement) + (compareFunc((char *)pQue + getRightChild(parent, pQue, sizeOfElement), (char *)pQue + getLeftChild(parent, pQue, sizeOfElement)) * sizeOfElement), parent))
#endif // !connectionMacros

void pQue_enque(void *item, size_t sizeOfElement, bool (*compareFunc)(const void *parent, const void *child))
{
    //first time stuff
    static void *lastUnit = NULL;
    static unsigned long previouslyMalloced;
    if (pQue == NULL)
    {
        pQue = malloc(sizeOfElement * 100);
        lastUnit = (char *)pQue + sizeOfElement * 99;
        previouslyMalloced = 100;
        endLoc = pQue;
    }

    memcpy(endLoc, item, sizeOfElement); // the enqueuing
    void *child = endLoc;
    void *parent;
    void *temp = malloc(sizeOfElement);
    while ((child != pQue) && compareFunc(child, parent = findParent(pQue, child, sizeOfElement)))
    { //heapify
        //swap parent and child
        memcpy(temp, child, sizeOfElement);
        memcpy(child, parent, sizeOfElement);
        memcpy(parent, temp, sizeOfElement);
        child = parent;
    }
    free(temp);
    //increment endloc
    if (endLoc == lastUnit)
    {
        previouslyMalloced *= 2;
        endLoc = ((previouslyMalloced / 2 - 1) * sizeOfElement) + (char *)(pQue = realloc(pQue, sizeOfElement * previouslyMalloced));
        lastUnit = (char *)pQue + sizeOfElement * (previouslyMalloced - 1);
    }
    endLoc = (char *)endLoc + sizeOfElement;
}
void *pQue_deque(size_t sizeOfElement, bool (*compareFunc)(const void *p1, const void *p2))
{
    //if the end location == the start, or there is no start
    if ((pQue == NULL) || (endLoc <= pQue))
        return NULL;
    endLoc = (char *)endLoc - sizeOfElement;
    void *returnVal = malloc(sizeOfElement);
    memcpy(returnVal, pQue, sizeOfElement);
    memcpy(pQue, endLoc, sizeOfElement);
    void *parent = pQue;
    void *child = pQue;
    void *temp = malloc(sizeOfElement);
    while ((getRightChild(parent, pQue, sizeOfElement) < (char *)endLoc - (char *)pQue) &&
           correctChild(pQue, child, parent, sizeOfElement, compareFunc))
    { //heapify
        //swap child and parent
        memcpy(temp, child, sizeOfElement);
        memcpy(child, parent, sizeOfElement);
        memcpy(parent, temp, sizeOfElement);
        parent = child;
    }
    //if one of the children is there
    if ((child == parent) && (getLeftChild(parent, pQue, sizeOfElement) < (char *)endLoc - (char *)pQue) &&
        compareFunc(child = (char *)pQue + getLeftChild(parent, pQue, sizeOfElement), parent))
    {
        memcpy(temp, child, sizeOfElement);
        memcpy(child, parent, sizeOfElement);
        memcpy(parent, temp, sizeOfElement);
    }
    free(temp);
    return returnVal;
}
void doneWith_pQue(void)
{
    free(pQue);
    pQue = NULL;
}

#ifdef pQue_test
bool compareFunc_min(const void *p1, const void *p2)
{
    return *((int *)p1) < *((int *)p2);
}
bool compareFunc_max(const void *p1, const void *p2)
{
    return *((int *)p1) > *((int *)p2);
}
bool (*compareFuncs[])(const void *p1, const void *p2){
    compareFunc_max, compareFunc_min};
//let user test funcs
void testStuff(void)
{
    bool stillTesting = 1;
    char ch; //for reading user input
    printf("do you want a minHeap(1) or maxHeap(0): ");
    bool heapType = getchar() - '0'; //is it a minHeap or maxHeap
    assert(getchar() == '\n');

    //testing loop
    while (stillTesting)
    {
        //action
        printf("do you want to enque(1) or deque(0): ");
        if (getchar() - '0')
        { //enque
            assert(getchar() == '\n');
            printf("what number do you want to enque: ");
            int enqueNum = 0;
            while ((ch = getchar()) != '\n')
                enqueNum = (enqueNum * 10) + (ch - '0');
            pQue_enque(&enqueNum, sizeof(int), compareFuncs[heapType]);
        }
        else
        { //deque
            assert(getchar() == '\n');
            int *dequed = (int *)pQue_deque(sizeof(int), compareFuncs[heapType]);
            if (dequed)
                printf("The value dequed is %d\n", *dequed);
            else
                printf("nothing to deque\n");
            free(dequed);
        }

        //tree
        printf("do you want the see the tree(1) or not(0): ");
        if (getchar() - '0')
        { //they want to see the priority queue
            int *toPrint = (int *)pQue;
            int maxCurrRow = 1;
            int numInRow = 0;
            while (toPrint < endLoc)
            { //print the contents of the priority queue
                printf("%d ", *toPrint);
                numInRow++;
                toPrint++;
                if (numInRow == maxCurrRow)
                {
                    fputc('\n', stdout);
                    maxCurrRow *= 2;
                    numInRow = 0;
                }
            }
            fputc('\n', stdout);
        }
        assert(getchar() == '\n');

        //should I stop?
        printf("do you want to contine(1) or stop(0): ");
        stillTesting = getchar() - '0';
        assert(getchar() == '\n');
    }
    doneWith_pQue();
}
#endif // pQue_test