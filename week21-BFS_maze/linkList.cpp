#include "linkList.h"
#include <stdlib.h>
stack *push(stack *start, int storage)
{
    stack *newStart = (stack *)malloc(sizeof(stack));
    newStart->storage = storage;
    newStart->next = start;
    return newStart;
}
int pop(stack **start)
{
    int storage;
    storage = (*start)->storage;
    struct stack *old = *start;
    (*start) = (*start)->next;
    free(old);
    return storage;
}
queue *enque(queue *start, int storage)
{
    queue *current;
    queue *newEnd = (queue *)malloc(sizeof(queue));
    newEnd->next = NULL;
    newEnd->storage = storage;
    if (start != NULL)
    {
        for (current = start;
             current->next != NULL;
             current = current->next)
            ;
        current->next = newEnd;
    }
    else
        start = newEnd;
    return start;
}
int deque(queue **start)
{
    int storage;
    storage = (*start)->storage;
    queue *old = *start;
    (*start) = (*start)->next;
    free(old);
    return storage;
}