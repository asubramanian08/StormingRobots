struct stack
{
    double storage;
    char oper = 0;
    stack *next;
};
struct queue
{
    double storage;
    char opr = 0;
    queue *next;
};
stack *push(stack *start, double input, char oper);
double pop(stack **start);
queue *enque(queue *start, double storage, char oper);
double deque(queue **start);