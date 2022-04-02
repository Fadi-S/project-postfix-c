#include <stdio.h>
#include "Stack.h"
#include "string.h"

/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME multi-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
char* infixToPostfix(char* infix)
{
    /* TODO: ADD YOUR CODE HERE */
}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
}


void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main() {
    char infixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        char*postfix = infixToPostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }

    return 0;
}
