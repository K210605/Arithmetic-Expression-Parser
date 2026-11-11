#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 100

typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s);
int isEmpty(const Stack *s);
int isFull(const Stack *s);
int push(Stack *s, char c);
int pop(Stack *s, char *c);
int peek(const Stack *s, char *c);

#endif