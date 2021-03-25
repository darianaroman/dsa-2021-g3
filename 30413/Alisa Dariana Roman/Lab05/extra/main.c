#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
first i observe that the operators are only on positions that represent powers of 2
also, the operands are always leafs
*  -  1.05  +  -55  22  10.3
1  2   3    4   5   6     7

algorithm:
- create binary tree with operators, when an operand is met stop there with that branch, operand remains leaf
**/

typedef struct node_type
{
    char item[10];
    struct node_type *left, *right;
} NodeT;

int isOperator(char item[]) /// it's an operator if the size of <item[]> is 1 and is +, -, * or /
{
    if(strlen(item) == 1) {
        char c = item[0];
        if (c == '+') {
            return 1;
        }
        if (c == '-') {
            return 1;
        }
        if (c == '*') {
            return 1;
        }
        if (c == '/') {
            return 1;
        }
        return 0;
    }
    return 0;   /// return 0 if size is greater than 1
}

NodeT *createNode(char item[])
{
    NodeT *p = (NodeT*) malloc (sizeof(NodeT));
    if (p) {
        strcpy(p->item, item);
        p->left = p->right = NULL;
    }
    return p;
}

NodeT *createBinTree(FILE *fileI)
{
    NodeT *p;
    char item[100];
    fscanf(fileI, "%s", item);
    if ( isOperator(item) ) {
        p = createNode(item);
        p->left = createBinTree(fileI);
        p->right = createBinTree(fileI);
    }
    else {
        p = createNode(item);
    }
    return p;
}

void traversalInOrder (NodeT *root, FILE *fileO, int level)
{
    if(root != NULL) {
        traversalInOrder(root->left, fileO, level + 1);

        for(int i = 0; i <= level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%s\n", root->item);

        traversalInOrder(root->right, fileO, level + 1);
    }
}

void displayTree (NodeT *root, FILE *fileO)
{
    if(root != NULL) {
        fprintf(fileO, "(");
        displayTree(root->left, fileO);
        fprintf(fileO, "%s", root->item);
        displayTree(root->right, fileO);
        fprintf(fileO, ")");
    }
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    NodeT *root = createBinTree(fileI);

    fprintf(fileO, "tree inorder:\n");
    traversalInOrder(root, fileO, 0);

    fprintf(fileO, "the expression is:\n");
    displayTree(root, fileO);

    return 0;
}
