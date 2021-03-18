/*5.2. Develop a modular program which demonstrates the BST operations in a tree which contains as keys the uppercase
letters of the Roman alphabet. The operations are:
• insert, coded in input as i<letter> (e.g. iD) attempts to insert letter D;
• delete, coded in input as d<letter> (e.g. dF) attempts to delete node with key F;
• find, coded in input as f<letter> (e.g. fG) attempts to find node with key G;
• traversals (pre, in, post-order), coded in input as t<letter> (e.g. tp attempts to list nodes in preorder, tP
attempts to list nodes in postorder, ti) attempts to list nodes in inorder;
• getting the minimum and maximum specified in input as gm (minimum), gM (maximum);
Use files, with names given on the command line for input and output.*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEFT 1
#define RIGHT 2
typedef struct bst_node
{
    char key;
    struct bst_node *left, *right;
} BSTNodeT;
BSTNodeT *root;
void fatalError(const char *msg, FILE *g)
{
    fprintf(g, msg);
    fprintf(g, "\n");
    exit (1);
}
void preorder(BSTNodeT *p, int level, FILE *g)
{
    int i;
    if (p != NULL)
    {
        for (i = 0; i <= level; i++) fprintf(g, " ");
        fprintf(g, "%c\n", p->key);
        preorder(p->left, level + 1, g);
        preorder(p->right, level + 1, g);
    }
}
void inorder(BSTNodeT *p, int level, FILE *g)
{
    int i;
    if (p != NULL)
    {
        inorder(p->left, level + 1, g);
        for (i = 0; i <= level; i++) fprintf(g, " ");
        fprintf(g, "%c\n", p->key);
        inorder(p->right, level + 1, g);
    }
}
void postorder(BSTNodeT *p, int level, FILE *g)
{
    int i;
    if (p != NULL)
    {
        postorder(p->left, level + 1, g);
        postorder(p->right, level + 1, g);
        for (i = 0; i <= level; i++) fprintf(g, " ");
        fprintf(g, "%c\n", p->key);
    }
}
BSTNodeT *recInsert(BSTNodeT *root, char *key, FILE *g)
{
    BSTNodeT *p;
    if (root == NULL)
    {
        p = (BSTNodeT *) malloc(sizeof(BSTNodeT));
        p->key = key;
        p->left = p->right = NULL;
        root = p;
        return root;
    }
    else
    {
        if (key < root->key)
            root->left = recInsert(root ->left, key, g);
        else if (key > root->key)
            root->right = recInsert(root ->right, key, g);
        else
            fprintf(g, "\nNode of key=%c already exists\n", key);
    }
    return root;
}
BSTNodeT *delNode(BSTNodeT *root, char *key, FILE *g)
{
    BSTNodeT *p;
    BSTNodeT *pParent;
    BSTNodeT *pRepl;
    BSTNodeT *pReplParent;
    int direction;
    if (root == NULL) return NULL;
    p = root;
    pParent = NULL;
    while (p != NULL && p->key != key)
    {
        if (key < p->key)
        {
            /* search left branch */
            pParent = p;
            p = p->left;
            direction = LEFT;
        }
        else
        {
            /* search right branch */
            pParent = p;
            p = p->right;
            direction = RIGHT;
        }
    }
    if (p == NULL)
    {
        fprintf(g, "\nNo node of key value=%c\n", key);
        return root;
    }
    /* node of key p found */
    if (p->left == NULL)
        pRepl = p->right;
    else if (p->right == NULL)
        pRepl = p->left;
    else
    {
        /* both children present */
        pReplParent = p;
        pRepl = p->right;
        while (pRepl->left != NULL)
        {
            pReplParent = pRepl;
            pRepl = pRepl->left;
        }
        if (pReplParent != p)
        {
            pReplParent->left = pRepl->right;
            pRepl->right = p->right;
        }
        pRepl->left = p->left;
    }
    free(p);
    fprintf(g, "\nDeletion of node %c completed\n", key);
    if (pParent == NULL)
        return pRepl;
    else
    {
        if (direction == LEFT)
            pParent->left = pRepl;
        else
            pParent->right = pRepl;
        return root;
    }
}
void delTree(BSTNodeT *root)
{
    if (root != NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }
}
char maxTree(BSTNodeT *root)
{
    if(root == NULL) return 0;
    if(root->right != NULL)
    maxTree(root->right);
    else return root->key;
}
char minTree(BSTNodeT *root)
{
    if(root == NULL) return 0;
    if(root->left != NULL)
    minTree(root->left);
    else return root->key;
}
int main(int argc, char const **argv)
{
    FILE *f = fopen(argv[1], "r");
    FILE *g = fopen(argv[2], "w");
    char *key;
    char *op;
    char *ch;
    root = NULL;
    while((op = fgetc(f)) != EOF)
    {
        //fprintf(g, "\nOperation: %c", op);
        if(op != 'g')
        {
            key = fgetc(f);
            //fprintf(g, "\nKey: %c\n", key);
            if(op == 'i')
            {
                root = recInsert(root, key, g);
                if(root == NULL)
                    fprintf(g, "Node %c not inserted\n", key);
                else fprintf(g, "Node %c inserted successfully\n", key);
            }
            else
            {
                if(op == 'd')
                    delNode(root, key, g);
                else{
                    if(op == 't'){
                        if(key == 'p'){
                            fprintf(g, "\nPreorder listing:\n");
                            preorder(root, 0, g);
                        }
                        else{
                            if(key == 'P'){
                                fprintf(g, "\nPostorder listing:\n");
                                postorder(root, 0, g);
                            }
                            else {
                                fprintf(g, "\nInorder listing:\n");
                                inorder(root, 0, g);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            ch = fgetc(f);
            if(op == 'g' && ch == 'm')
                fprintf(g, "\nMinimum is: %c\n", minTree(root));
            else fprintf(g, "\nMaximum is: %c\n", maxTree(root));
        }
        ch = fgetc(f);
    }
    delTree(root);
    fclose(f);
    fclose(g);
    return 0;
}
