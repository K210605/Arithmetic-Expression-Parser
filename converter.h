#ifndef CONVERTER_H
#define CONVERTER_H

#define MAX_EXPR 256

int isOperator(char c);
int precedence(char op);
int isRightAssociative(char op);
int infixToPostfix(const char *infix, char *postfix);

#endif