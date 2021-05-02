struct stack
{
	int storage;
	stack* next;
};
stack* push(stack* start, int storage);
int pop(stack** start);
struct queue
{
	int storage;
	queue* next;
};
queue* enque(queue* start, int storage);
int deque(queue** start);