#include <stdlib.h>
#include "LinkedList.h"
#include <stdio.h>

typedef struct {
    Node * top;
} Stack;

Stack *initialize()
{
    Stack *stack = malloc(sizeof(Stack));

    stack->top = newNode(-1);

    return stack;
}


float peek(Stack* stack)
{
    return getData(getPrevious(stack->top));
}

void push(Stack* stack, float item)
{
    insertNodeBefore(stack->top, item);
}

float pop(Stack* stack)
{
    float item = peek(stack);

    stack->top->previous = deleteNode(getPrevious(stack->top));

    return item;
}

void destroy(Stack *stack)
{
    free(stack);
}

int isEmpty(Stack *stack)
{
    return getPrevious(stack->top) == NULL;
}