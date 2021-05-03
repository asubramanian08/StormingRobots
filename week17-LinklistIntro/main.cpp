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
//there should be a user written compare function that you call to see where to place
struct linklist
{
    int number;
    linklist *next;
};

linklist *insert(int insertNum, linklist *start)
{
    linklist *current;
    linklist *previous = start;
    for (current = start;
         (current != NULL) && (current->number < insertNum);
         previous = current, current = current->next)
        ;
    linklist *insertNode = (linklist *)malloc(sizeof(linklist));
    insertNode->number = insertNum;
    insertNode->next = current;
    previous->next = insertNode;
    return start;
}
linklist *remove(int removeNum, linklist *start)
{
    linklist *current;
    linklist *previous = start;
    for (current = start;
         (current != NULL) && (current->number < removeNum);
         previous = current, current = current->next)
        ;
    if (current == NULL || current->number != removeNum)
        printf("nothing to remove\n");
    else
        previous->next = current->next;
    free(current);
    free(previous);
    return start;
}
//returns location if it can find and NULL if can't
linklist *find(int num, linklist *start)
{
    linklist *lookFor;
    for (lookFor = start;
         (lookFor != NULL) && (lookFor->number < num);
         lookFor = lookFor->next)
        ;
    if (lookFor->number > num)
        return NULL;
    else
        return lookFor;
}
int main(void)
{
    /*int x[] = { 4, 2, 6, 3, 1 };
	linklist* start = (linklist*)malloc(sizeof(linklist));
	start->number = 0;
	start->next = NULL;
	for (int i = 0; i < 5; i++)
		start = insert(x[i], start);
	start = remove(3, start);
	if (find(2, start)->number == 2)
		printf("find is success\n");
	else
		printf("find failed\n");
	for (; start != NULL; start = start->next)
		printf("%d", start->number);*/
    system("pause");
    return 0;
}