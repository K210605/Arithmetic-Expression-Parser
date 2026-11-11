#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tree.h"
#include "converter.h"

#define NODE_STACK_SIZE MAX_EXPR
#define PREFIX_SIZE (MAX_EXPR * 4 + 1)

/* Creates a new tree node */
TreeNode *createNode(const char *value) {
    TreeNode *node = malloc(sizeof(TreeNode));

    if (node == NULL) {
        return NULL;
    }

    strncpy(node->value, value, MAX_TOKEN - 1);
    node->value[MAX_TOKEN - 1] = '\0';

    node->left = NULL;
    node->right = NULL;

    return node;
}

/* Frees the complete parse tree */
void freeTree(TreeNode *root) {
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}

/* Frees all trees remaining in the node stack */
static void freeNodeStack(TreeNode *stack[], int top) {
    for (int i = 0; i <= top; i++) {
        freeTree(stack[i]);
    }
}

/* Builds a binary expression tree from postfix expression */
TreeNode *buildTree(const char *postfix) {
    TreeNode *stack[NODE_STACK_SIZE];

    int top = -1;
    int i = 0;

    while (postfix[i] != '\0') {

        char token[MAX_TOKEN];
        int len = 0;

        TreeNode *node;

        /* Skip whitespace */
        if (isspace((unsigned char)postfix[i])) {
            i++;
            continue;
        }

        /* Read one token */
        while (postfix[i] != '\0' &&
               !isspace((unsigned char)postfix[i])) {

            if (len >= MAX_TOKEN - 1) {
                freeNodeStack(stack, top);
                return NULL;
            }

            token[len++] = postfix[i++];
        }

        token[len] = '\0';

        /* Create a new node */
        node = createNode(token);

        if (node == NULL) {
            freeNodeStack(stack, top);
            return NULL;
        }

        /* Handle operators */
        if (len == 1 && isOperator(token[0])) {

            if (top < 1) {
                freeTree(node);
                freeNodeStack(stack, top);
                return NULL;
            }

            node->right = stack[top--];
            node->left = stack[top--];
        }

        /* Check stack capacity */
        if (top >= NODE_STACK_SIZE - 1) {
            freeTree(node);
            freeNodeStack(stack, top);
            return NULL;
        }

        stack[++top] = node;
    }

    /* A valid postfix expression must produce one root */
    if (top != 0) {
        freeNodeStack(stack, top);
        return NULL;
    }

    return stack[0];
}

/* Preorder: Root -> Left -> Right */
void printPreorder(const TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%s ", root->value);

    printPreorder(root->left);
    printPreorder(root->right);
}

/* Inorder: Left -> Root -> Right */
void printInorder(const TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printInorder(root->left);

    printf("%s ", root->value);

    printInorder(root->right);
}

/* Postorder: Left -> Right -> Root */
void printPostorder(const TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printPostorder(root->left);
    printPostorder(root->right);

    printf("%s ", root->value);
}

/* Recursively prints the tree structure */
static void printSubtree(
    const TreeNode *node,
    const char *prefix,
    int isLast
) {
    char childPrefix[PREFIX_SIZE];

    int result;

    if (node == NULL) {
        return;
    }

    printf("%s%s%s\n",
           prefix,
           isLast ? "`-- " : "|-- ",
           node->value);

    result = snprintf(
        childPrefix,
        sizeof(childPrefix),
        "%s%s",
        prefix,
        isLast ? "    " : "|   "
    );

    if (result < 0 || (size_t)result >= sizeof(childPrefix)) {
        return;
    }

    printSubtree(node->left, childPrefix, 0);
    printSubtree(node->right, childPrefix, 1);
}

/* Prints the complete parse tree */
void printTree(const TreeNode *root) {
    if (root == NULL) {
        return;
    }

    printf("%s\n", root->value);

    printSubtree(root->left, "", 0);
    printSubtree(root->right, "", 1);
}