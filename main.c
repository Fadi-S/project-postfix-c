#include <stdio.h>
#include "Stack.h"
#include "string.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>

#define VERBOSE 0

// Check if expression is a float
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

// Calculate operator priority
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

// Add character to the end of a string
void str_append(char *str, char c) {
    char newStr[2];
    newStr[0] = c;
    newStr[1] = '\0';

    strcat(str, newStr);
}

// Pass operands and operator -> Calculate the result
float calculate(float operand1, float operand2, char operator) {
    if(VERBOSE == 1)
        printf("%f %c %f\n", operand1, operator, operand2);

    if (operator == '+') {
        return operand1 + operand2;
    }

    if (operator == '-') {
        return operand1 - operand2;
    }

    if (operator == '*') {
        return operand1 * operand2;
    }

    if (operator == '/') {
        return operand1 / operand2;
    }

    if (operator == '^') {
        return powf(operand1, operand2);
    }

    return 0;
}

char *infixToPostfix(char *infix) {
    char postfixTemp[strlen(infix)*3];
    strcpy(postfixTemp, "");
    Stack *operators = initialize();

    int i;
    int wasOperator = 1;
    for (i = 0; i < strlen(infix); ++i) { // Loop through all characters of infix expression
        if (infix[i] == ' ') continue; // In case of whitespace -> Skip

        // In case of number -> Get all number and out it in expression
        // Starts with a digit, dot or minus sign
        // EX: -4.5 , 55 , -7, 12.3
        if (isdigit(infix[i]) || infix[i] == '.' || (infix[i] == '-' && isdigit(infix[i + 1]) && wasOperator)) {
            wasOperator = 0; // Indicate that the last loop was a number not an operator
            do {
                str_append(postfixTemp, infix[i++]);
            } while (isdigit(infix[i]) || infix[i] == '.');

            str_append(postfixTemp, ' ');

            i--;
            continue;
        }

        // In case of a closed bracket -> Loop until you find an open bracket (
        if (infix[i] == ')') {
            // Loop until you find an open bracket (
            while (!isEmpty(operators)) {
                char opr =  (char) pop(operators);
                if (opr == '(') break;

                str_append(postfixTemp, opr);
                str_append(postfixTemp, ' ');
            }

            continue;
        }

        // In Case of an operator +-*/^ or (
        wasOperator = 1; // Indicate that the last loop was an operator not a number

        int priorityOfCurrent = getPriority(infix[i]);
        char peekOp = (char) peek(operators);
        // Pop and add to expression while priority of current operator
        // is bigger than that of the operator on
        // top
        while (
                !isEmpty(operators)
                && priorityOfCurrent <= getPriority(peekOp)
                && peekOp != '(')
        {
            str_append(postfixTemp, (char) pop(operators));
            str_append(postfixTemp, ' ');
            peekOp = (char) peek(operators);
        }

        push(operators, infix[i]);
    }

    // Dump all operators still in stack in the expression
    while (!isEmpty(operators)) {
        str_append(postfixTemp, (char) pop(operators));
        str_append(postfixTemp, ' ');
    }

    char *postfix = malloc(sizeof(infix) * 2);

    strcpy(postfix, postfixTemp);
    return postfix;
}

float evaluatePostfix(char *postfix) {
    Stack *s = initialize();
    char* operand = strtok(postfix, " ");

    while (operand) {
        if (isFloat(operand)) {
            push(s, atof(operand));

            operand = strtok(NULL, " ");
            continue;
        }

        float x = pop(s);
        float y = pop(s);
        float result = calculate(y, x, operand[0]);
        push(s, result);

        operand = strtok(NULL, " ");
    }

    if(isEmpty(s)) {
        fprintf(stderr, "Invalid Syntax\n");
        return -1;
    }

    return pop(s);
}

void replaceNewLineBySpace(char *string)
{
    while ((string = strstr(string, "\n")) != NULL)
    {
        *string = ' ';
    }
}

int main() {
    char infixExpr[256] = "";
    char *message = "Enter an expression you want to evaluate or type 'q' to exit: ";

    printf(message);
    while (fgets(infixExpr, 255, stdin) != NULL) {
        replaceNewLineBySpace(infixExpr);

        if (strcasecmp(infixExpr, "q ") == 0) {
            exit(0);
        }

        char *postfix = infixToPostfix(infixExpr);
        printf("Postfix : %s\n", postfix);
        float result = evaluatePostfix(postfix);
        printf("Result: %f\n\n", result);
        printf(message);

        free(postfix);
    }

    return 0;
}