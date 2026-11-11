#ifndef TREE_H
#define TREE_H

#define MAX_TOKEN 101

typedef struct TreeNode {
    char value[MAX_TOKEN];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *createNode(const char *value);
TreeNode *buildTree(const char *postfix);
void freeTree(TreeNode *root);

void printPreorder(const TreeNode *root);
void printInorder(const TreeNode *root);
void printPostorder(const TreeNode *root);
void printTree(const TreeNode *root);

#endif