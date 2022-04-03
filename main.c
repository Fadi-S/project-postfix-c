#include <stdio.h>
#include "Stack.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

int isFloat(char *number) {
    char *temp;

    strtod(number, &temp);
    if (temp == number) {
        return 0;
    }

    if (temp[strspn(temp, " \t\r\n")] != '\0') {
        return 0;
    }

    return 1;
}

int getPriority(char operator) {
    if (operator == '(' || operator == ')') {
        return 4;
    }

    if (operator == '^') {
        return 3;
    }

    if (operator == '*' || operator == '/' || operator == '%') {
        return 2;
    }

    if (operator == '+' || operator == '-') {
        return 1;
    }

    return 0;
}

void str_append(char*str, char c)
{
    str[strlen(str)] = c;
}

char *infixToPostfix(char *infix) {
    char *postfix = malloc(sizeof (infix));
    Stack *operators = initialize();

    int i;
    for (i = 0; i < strlen(infix); ++i) {
        if(infix[i] == ' ') continue;

        if (isdigit(infix[i]) || infix[i] == '.') {
            char number[15] = "";
            int numberIncr = 0;
            while (isdigit(infix[i]) || infix[i] == '.') {
                number[numberIncr++] = infix[i++];
            }
            i--;
            number[numberIncr] = ' ';

            strcat(postfix, number);
            continue;
        }

        if(infix[i] == ')') {
            while(!isEmpty(operators)) {
                char opr = (char) pop(operators);
                if(opr == '(') break;

                str_append(postfix, opr);
                str_append(postfix, ' ');
            }

            continue;
        }

        if(infix[i] == '(') {
            push(operators, infix[i]);
            continue;
        }

        int priorityOfCurrent = getPriority(infix[i]);

        while (priorityOfCurrent <= getPriority((char) peek(operators))) {
            str_append(postfix, (char) pop(operators));
            str_append(postfix, ' ');
        }

        push(operators, infix[i]);
    }

    while (!isEmpty(operators)) {
        str_append(postfix, (char) pop(operators));
        str_append(postfix, ' ');
    }

    return postfix;
}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluatePostfix(char *postfix) {
    /* TODO: ADD YOUR CODE HERE */
}


void replaceNewLineBySpace(char *s) {
    char *s1 = s;
    while ((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main() {
//    char infixExpr[256] = "";
//
//    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
//    while(fgets(infixExpr, 255, stdin) != NULL)
//    {
//        replaceNewLineBySpace(infixExpr);
//        char*postfix = infixToPostfix(infixExpr);
//        printf("Postfix : %s\n", postfix);
//        float result = evaluatePostfix(postfix);
//        printf("Result: %f\n\n", result);
//        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
//    }

    printf("%s", infixToPostfix("5.4 + 8 * 97 - ( 5 + 6 )"));

    return 0;
}
