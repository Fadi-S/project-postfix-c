#include <stdlib.h>
#include "LinkedList.h"

typedef struct {
    LinkedList *list;
} Stack;

Stack *initialize()
{
    Stack *stack = malloc(sizeof(Stack));

    stack->list = newLinkedList();

    return stack;
}

float peek(Stack* stack)
{
    return getData(getHead(stack->list));
}

void push(Stack* stack, float item)
{
    Node *node = newNode(item);

    setHead(stack->list, node);
}

float pop(Stack* stack)
{
    float item = peek(stack);

    deleteHead(stack->list);

    return item;
}

void destroy(Stack *stack)
{
    free(stack);
}

int isEmpty(Stack *stack)
{
    return isLinkedListEmpty(stack->list);
}


//typedef struct {
//    int top;
//    float *items;
//    int full;
//} Stack;
//
//Stack *initialize()
//{
//    Stack *stack = malloc(sizeof(Stack));
//    stack->items = malloc(100 * sizeof(float ));
//
//    stack->full = 100;
//
//    stack->top = 0;
//
//    return stack;
//}
//
//int maxElements(Stack *stack)
//{
//    return stack->full;
//}
//
//void push(Stack* stack, float item)
//{
//    stack->items[stack->top] = item;
//
//    stack->top++;
//}
//
//float peek(Stack* stack)
//{
//    return stack->items[stack->top-1];
//}
//
//float pop(Stack* stack)
//{
//    float item = peek(stack);
//
//    stack->top--;
//
//    return item;
//}
//
//void destroy(Stack *stack)
//{
//    free(stack->items);
//    free(stack);
//}
//
//int isEmpty(Stack *stack)
//{
//    return stack->top == 0;
//}