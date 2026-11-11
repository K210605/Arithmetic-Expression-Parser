#include <stdio.h>
#include <string.h>
#include "validator.h"
#include "converter.h"
#include "tree.h"

#define INPUT_BUF_SIZE 256
#define DEFAULT_TEST_FILE "tests.txt"

/* Reads one line from 'in' into buf. Removes the newline.
   Returns 1 on success, 0 on end of input.
   *tooLong is set to 1 if the line did not fit in the buffer. */
static int readLine(FILE *in, char *buf, int size, int *tooLong) {
    size_t len;

    *tooLong = 0;
    if (fgets(buf, size, in) == NULL) {
        return 0;
    }

    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[--len] = '\0';
    } else if (len == (size_t)size - 1) {
        int ch;
        while ((ch = fgetc(in)) != '\n' && ch != EOF) {
        }
        *tooLong = 1;
    }

    if (len > 0 && buf[len - 1] == '\r') {
        buf[len - 1] = '\0';
    }
    return 1;
}

/* Runs the full pipeline on one expression.
   Returns 1 if the expression was valid, 0 otherwise. */
static int processExpression(const char *expr) {
    char err[ERR_MSG_SIZE];
    char postfix[MAX_EXPR];
    TreeNode *root;

    if (!validateExpression(expr, err)) {
        printf("\n[ERROR] %s\n", err);
        return 0;
    }

    if (!infixToPostfix(expr, postfix)) {
        printf("\n[ERROR] Could not convert expression to postfix\n");
        return 0;
    }

    root = buildTree(postfix);
    if (root == NULL) {
        printf("\n[ERROR] Could not build the parse tree\n");
        return 0;
    }

    printf("\nPostfix   : %s\n", postfix);

    printf("Preorder  : ");
    printPreorder(root);
    printf("\nInorder   : ");
    printInorder(root);
    printf("\nPostorder : ");
    printPostorder(root);

    printf("\n\nParse Tree:\n");
    printTree(root);

    freeTree(root);
    return 1;
}

static void printMenu(void) {
    printf("\n========================================\n");
    printf("     ARITHMETIC EXPRESSION PARSER\n");
    printf("========================================\n");
    printf("  1. Parse one expression\n");
    printf("  2. Parse multiple expressions\n");
    printf("  3. Run expressions from a file\n");
    printf("  4. Help\n");
    printf("  0. Exit\n");
    printf("----------------------------------------\n");
    printf("Enter your choice: ");
}

static void printHelp(void) {
    printf("\n------------------- HELP -------------------\n");
    printf("Supported operators (highest precedence first):\n");
    printf("  ^        exponent         right to left\n");
    printf("  * / %%    multiply/divide  left to right\n");
    printf("  + -      add/subtract     left to right\n");
    printf("\nOperands : numbers (12, 3.5) and names (a, x1)\n");
    printf("Brackets : ( ) are allowed and can be nested\n");
    printf("\nExamples : 3 + 4 * 2\n");
    printf("           (a + b) * c\n");
    printf("           2 ^ 3 ^ 2\n");
    printf("\nNot supported: negative numbers like -5\n");
    printf("--------------------------------------------\n");
}

static void parseOne(void) {
    char input[INPUT_BUF_SIZE];
    int tooLong;

    printf("\nEnter expression: ");
    if (!readLine(stdin, input, sizeof(input), &tooLong)) {
        return;
    }
    if (tooLong) {
        printf("\n[ERROR] Input too long\n");
        return;
    }
    processExpression(input);
}

static void parseMultiple(void) {
    char input[INPUT_BUF_SIZE];
    int tooLong;
    int count = 0;

    printf("\nEnter one expression per line.\n");
    printf("Press Enter on an empty line to go back to the menu.\n");

    while (1) {
        printf("\nExpression %d > ", count + 1);
        if (!readLine(stdin, input, sizeof(input), &tooLong)) {
            break;
        }
        if (tooLong) {
            printf("\n[ERROR] Input too long\n");
            continue;
        }
        if (input[0] == '\0') {
            break;
        }
        processExpression(input);
        count++;
    }

    printf("\n%d expression(s) processed.\n", count);
}

static void runFile(void) {
    char name[INPUT_BUF_SIZE];
    char input[INPUT_BUF_SIZE];
    int tooLong;
    int total = 0;
    int valid = 0;
    FILE *fp;

    printf("\nFile name (press Enter for %s): ", DEFAULT_TEST_FILE);
    if (!readLine(stdin, name, sizeof(name), &tooLong) || tooLong) {
        printf("\n[ERROR] Invalid file name\n");
        return;
    }
    if (name[0] == '\0') {
        strcpy(name, DEFAULT_TEST_FILE);
    }

    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("\n[ERROR] Cannot open file '%s'\n", name);
        return;
    }

    while (readLine(fp, input, sizeof(input), &tooLong)) {
        if (input[0] == '\0') {
            continue;
        }
        if (input[0] == '#') {
            printf("\n%s\n", input);
            continue;
        }
        printf("\n----------------------------------------\n");
        printf("Expression: %s\n", input);
        if (tooLong) {
            printf("\n[ERROR] Input too long\n");
        } else if (processExpression(input)) {
            valid++;
        }
        total++;
    }
    fclose(fp);

    printf("\n========== SUMMARY ==========\n");
    printf("Total: %d | Valid: %d | Invalid: %d\n", total, valid, total - valid);
}

int main(void) {
    char choice[INPUT_BUF_SIZE];
    int tooLong;
    int running = 1;

    while (running) {
        printMenu();

        if (!readLine(stdin, choice, sizeof(choice), &tooLong)) {
            break;
        }

        if (tooLong || strlen(choice) != 1) {
            printf("\n[ERROR] Invalid choice. Please enter a number from 0 to 4.\n");
            continue;
        }

        switch (choice[0]) {
            case '1':
                parseOne();
                break;
            case '2':
                parseMultiple();
                break;
            case '3':
                runFile();
                break;
            case '4':
                printHelp();
                break;
            case '0':
                running = 0;
                break;
            default:
                printf("\n[ERROR] Invalid choice. Please enter a number from 0 to 4.\n");
                break;
        }
    }

    printf("\nThank you for using Arithmetic Expression Parser. Goodbye!\n");
    return 0;
}