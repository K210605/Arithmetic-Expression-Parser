#include "stack.h"

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(const Stack *s) {
    return s->top == -1;
}

int isFull(const Stack *s) {
    return s->top == MAX_SIZE - 1;
}

int push(Stack *s, char c) {
    if (isFull(s)) {
        return 0;
    }
    s->top++;
    s->data[s->top] = c;
    return 1;
}

int pop(Stack *s, char *c) {
    if (isEmpty(s)) {
        return 0;
    }
    *c = s->data[s->top];
    s->top--;
    return 1;
}

int peek(const Stack *s, char *c) {
    if (isEmpty(s)) {
        return 0;
    }
    *c = s->data[s->top];
    return 1;
}