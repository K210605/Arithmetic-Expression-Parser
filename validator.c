#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validator.h"
#include "converter.h"

static int isOperandChar(char c) {
    return isalnum((unsigned char)c) || c == '.';
}

int validateExpression(const char *expr, char *errMsg) {
    int i = 0;
    int depth = 0;
    int expectOperand = 1;
    char prev = 0;

    if (strlen(expr) > MAX_INPUT_LEN) {
        sprintf(errMsg, "Expression too long (maximum %d characters)",
                MAX_INPUT_LEN);
        return 0;
    }

    while (expr[i] != '\0') {
        char c = expr[i];

        if (isspace((unsigned char)c)) {
            i++;
            continue;
        }

        if (isOperandChar(c)) {
            int start = i;
            int dots = 0;
            int hasLetter = 0;

            if (!expectOperand) {
                sprintf(errMsg, "Missing operator before operand at position %d",
                        i + 1);
                return 0;
            }

            while (isOperandChar(expr[i])) {
                if (expr[i] == '.') {
                    dots++;
                }
                if (isalpha((unsigned char)expr[i])) {
                    hasLetter = 1;
                }
                i++;
            }

            if (dots > 1 ||
                (dots == 1 && hasLetter) ||
                (hasLetter && isdigit((unsigned char)expr[start])) ||
                (i - start == 1 && dots == 1)) {
                snprintf(errMsg, ERR_MSG_SIZE,
                          "Invalid operand at position %d", start + 1);
                return 0;
            }

            expectOperand = 0;
            prev = c;
            continue;
        }

        if (c == '(') {
            if (!expectOperand) {
                sprintf(errMsg, "Missing operator before '(' at position %d",
                        i + 1);
                return 0;
            }
            depth++;
            prev = c;
            i++;
            continue;
        }

        if (c == ')') {
            if (depth == 0) {
                sprintf(errMsg, "Unmatched ')' at position %d", i + 1);
                return 0;
            }
            if (expectOperand) {
                if (prev == '(') {
                    sprintf(errMsg, "Empty parentheses '()' at position %d",
                            i + 1);
                } else {
                    sprintf(errMsg, "Missing operand before ')' at position %d",
                            i + 1);
                }
                return 0;
            }
            depth--;
            prev = c;
            i++;
            continue;
        }

        if (isOperator(c)) {
            if (expectOperand) {
                if (isOperator(prev)) {
                    sprintf(errMsg, "Consecutive operators '%c%c' at position %d",
                            prev, c, i + 1);
                } else {
                    sprintf(errMsg,
                            "Missing operand before operator '%c' at position %d",
                            c, i + 1);
                }
                return 0;
            }
            expectOperand = 1;
            prev = c;
            i++;
            continue;
        }

        sprintf(errMsg, "Invalid character '%c' at position %d", c, i + 1);
        return 0;
    }

    if (prev == 0) {
        sprintf(errMsg, "Expression is empty");
        return 0;
    }
    if (expectOperand && isOperator(prev)) {
        sprintf(errMsg, "Expression ends with operator '%c'", prev);
        return 0;
    }
    if (depth > 0) {
        sprintf(errMsg, "Missing closing parenthesis ')' (%d unclosed)", depth);
        return 0;
    }

    return 1;
}