//Things were compiled differently due to file name change
#include "linkList.h"
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
//stack with push, pop and enque, deque
double getNum(char *ch)
{
    double total = 0;
    while ((*ch >= '0') && (*ch <= '9'))
    {
        total = total * 10 + *ch - '0';
        *ch = getchar();
    }
    return total;
}
int operOrder(char operation)
{
    switch (operation)
    {
    case '+':
    case '-':
        return 0;
        break;
    case '/':
    case '%':
    case '*':
        return 1;
        break;
    case '^':
        return 2;
        break;
    case ')':
        return -2;
        break;
    default:
        return -1;
        break;
    }
}
char brackets(stack **operators, queue **numbers)
{
    char curr = '?';
    while ((*operators != NULL) && ((*operators)->oper != '('))
    {
        *numbers = enque(*numbers, 0, (*operators)->oper);
        curr = pop(operators);
    }
    if (*operators != NULL)
        pop(operators);
    else
        curr = '\0';
    return curr;
}
queue *popRemaining(stack *operations, queue *made)
{
    while (operations != NULL)
        enque(made, 0, pop(&operations));
    return made;
}
void evaluate(queue *expression, stack **currNum)
{
    double num1;
    double num2;
    *currNum = NULL;
    while (expression != NULL)
    {
        if (expression->opr == 0) //it is a number
            *currNum = push(*currNum, deque(&expression), 0);
        else if (expression->opr == '(')
        {
            *currNum = NULL;
            return;
        }
        else //a regular operator
        {
            num2 = pop(currNum);
            num1 = pop(currNum);
            switch ((char)deque(&expression))
            {
            case '+':
                *currNum = push(*currNum, num1 + num2, 0);
                break;
            case '-':
                *currNum = push(*currNum, num1 - num2, 0);
                break;
            case '/':
                *currNum = push(*currNum, num1 / num2, 0);
                break;
            case '%':
                *currNum = push(*currNum, (int)num1 % (int)num2, 0);
                break;
            case '*':
                *currNum = push(*currNum, num1 * num2, 0);
                break;
            case '^':
                *currNum = push(*currNum, pow(num1, num2), 0);
                break;
            default:
                printf("You used an expression that wasn't valid");
                break;
            }
        }
    }
}
int main(void)
{
    stack *operators = NULL;
    queue *expression = NULL;
    printf("enter and expression to calculate: ");
    char ch = getchar();
    while (ch != '\n') //get the expression;
    {
        if (ch <= '9' && ch >= '0')
            expression = enque(expression, getNum(&ch), 0);
        else
        {
            if (ch != ' ')
            {
                if (operators != NULL && (operOrder(ch) != -1) && (operOrder(operators->oper) >= operOrder(ch)))
                    expression = enque(expression, 0, pop(&operators));
                if (ch != ')')
                    operators = push(operators, 0, ch);
                else
                {
                    ch = brackets(&operators, &expression);
                    if (ch == '\0')
                    { //brackets desplayed a problem
                        printf("Error: Imbalanced barackets\n");
                        return 0;
                    }
                }
            }
            ch = getchar();
        }
    }
    expression = popRemaining(operators, expression);
    evaluate(expression, &operators);
    if (operators != NULL)
        printf("%f\n", operators->storage);
    else
        printf("Imbalanced brackets\n");
    system("pause");
    return 0;
}
