#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
    char key;
    struct node_type *left, *right;
} BSTNodeT;

BSTNodeT *createNode(char givenKey)
{
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
        p->key = givenKey;
        p->left = p-> right = NULL;
    }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char key,FILE *fo)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
        root = createNode(key);
    else
    {
        if (key < root->key)
            root->left = insertNode(root->left, key, fo);
        else if (key > root->key)
            root->right = insertNode(root ->right, key, fo);
        else
            printf("\nNode with key = %c already exists\n", key);
    }
    return root;
}

BSTNodeT *findNode(BSTNodeT *root, char givenKey)
{
    if (root == NULL) return NULL; /* empty tree */
    BSTNodeT *p;
    for (p = root; p != NULL;)
    {
        if (givenKey == p->key) return p;
        else if (givenKey < p->key) p = p->left;
        else                   p = p->right;
    }
    return NULL; /* not found */
}


BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->left!=NULL) /* Go to the left sub tree to find the min element */
        return findMin(node->left);

    else
        return node;
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->right) /* Go to the left sub tree to find the min element */
        return findMax(node->right);
    else
        return node;
}

BSTNodeT* delNode(BSTNodeT* node, char key, FILE *fo)
{
    if(node == NULL)
    {
        fprintf(fo,"Element Not Found\n");
    }
    else if(key < node->key)
    {
        // must be in left subtree
        node->left = delNode(node->left, key, fo);
    }
    else if(key > node->key)
    {
        // must be in right subtree
        node->right = delNode(node->right, key, fo);
    }
    else
    {
        // found node
        /* Now We can delete this node and replace with either minimum element
           in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            BSTNodeT *temp = findMax(node->left);
            node -> key = temp->key;
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = delNode(node->right, temp->key, fo);
        }
        else
        {
            /* If there is only one or zero children then we can directly
               remove it from the tree and connect its parent to its child */
            BSTNodeT *temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp); /* temp is longer required */
        }
    }
    return node;
}

void preorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        fprintf(fo, "%c ", p->key );
        preorder(p->left, fo);
        preorder(p->right, fo);
    }
}
void inorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        inorder(p->left, fo);
        fprintf(fo, "%c ", p->key );
        inorder(p->right, fo);
    }
}
void postorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        postorder(p->left, fo);
        postorder(p->right, fo);
        fprintf(fo, "%c ", p->key );
    }
}
void operation(char instr, char lett, BSTNodeT *root, FILE *fo)
{
    switch (instr)
    {
    case 'i':
        if(root->key==' ')
            root->key=lett; ///i'm managing finding the root of the tree
        else
            insertNode(root,lett,fo);
        break;
    case 'd':
        delNode(root, lett, fo);
        break;

    case 'f':
    {
        if(findNode(root, lett)==NULL)
            fprintf(fo, "Node %c not found\n", lett);
        else fprintf(fo, "Node %c found\n", lett);
    }
    break;

    case 't':
        switch(lett)
        {
        case 'p':
        {
            preorder(root, fo);
            fprintf(fo,"\n");
        }
        break;

        case 'P':
        {
            postorder(root, fo);
            fprintf(fo,"\n");
        }
        break;

        case 'i':
        {
            inorder(root, fo);
            fprintf(fo,"\n");
        }
        break;
        }
        break;

    case 'g':
        switch(lett)
        {
        case 'm':
        {
            BSTNodeT *p=findMin(root);
            fprintf(fo, "The minimum key in the tree is %c\n",p->key);
        }
        break;

        case 'M':
        {
            BSTNodeT *p=findMax(root);
            fprintf(fo, "The maximum key in the tree is %c\n",p->key);
        }
        break;
        }
        break;
    }
}

int main(int argc, char **argv)
{
    FILE *fi=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");

    char op[3];
    BSTNodeT *root=createNode(' '); ///this will help me find the root of the tree

    while(fscanf(fi,"%s",&op)!=EOF)
        operation(op[0],op[1],root,fo);

    fclose(fi);
    fclose(fo);
    return 0;
}
