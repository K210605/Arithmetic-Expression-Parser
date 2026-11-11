#include <ctype.h>
#include "converter.h"
#include "stack.h"

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' ||
           c == '/' || c == '%' || c == '^';
}

int precedence(char op) {
    switch (op) {
        case '^':
            return 3;
        case '*':
        case '/':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

int isRightAssociative(char op) {
    return op == '^';
}

static int isOperandChar(char c) {
    return isalnum((unsigned char)c) || c == '.';
}

static int appendOperator(char *postfix, int *j, char op) {
    if (*j >= MAX_EXPR - 3) {
        return 0;
    }
    postfix[(*j)++] = op;
    postfix[(*j)++] = ' ';
    return 1;
}

int infixToPostfix(const char *infix, char *postfix) {
    Stack s;
    char top;
    int i = 0;
    int j = 0;

    initStack(&s);

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isspace((unsigned char)c)) {
            i++;
            continue;
        }

        if (isOperandChar(c)) {
            while (isOperandChar(infix[i])) {
                if (j >= MAX_EXPR - 3) {
                    return 0;
                }
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            continue;
        }

        if (c == '(') {
            if (!push(&s, c)) {
                return 0;
            }
            i++;
            continue;
        }

        if (c == ')') {
            int found = 0;
            while (pop(&s, &top)) {
                if (top == '(') {
                    found = 1;
                    break;
                }
                if (!appendOperator(postfix, &j, top)) {
                    return 0;
                }
            }
            if (!found) {
                return 0;
            }
            i++;
            continue;
        }

        if (isOperator(c)) {
            while (peek(&s, &top) && isOperator(top) &&
                   (precedence(top) > precedence(c) ||
                    (precedence(top) == precedence(c) &&
                     !isRightAssociative(c)))) {
                pop(&s, &top);
                if (!appendOperator(postfix, &j, top)) {
                    return 0;
                }
            }
            if (!push(&s, c)) {
                return 0;
            }
            i++;
            continue;
        }

        return 0;
    }

    while (pop(&s, &top)) {
        if (top == '(') {
            return 0;
        }
        if (!appendOperator(postfix, &j, top)) {
            return 0;
        }
    }

    if (j > 0 && postfix[j - 1] == ' ') {
        j--;
    }
    postfix[j] = '\0';
    return 1;
}