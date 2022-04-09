#ifndef LAB_6_STACK_H
#define LAB_6_STACK_H

typedef struct Stack Stack;

Stack *initialize();

void push(Stack* stack, float item);
float peek(Stack* stack);
float pop(Stack* stack);
void destroy(Stack *stack);
int isEmpty(Stack *stack);

#endif //LAB_6_STACK_H
