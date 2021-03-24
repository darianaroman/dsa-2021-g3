#include <stdio.h>
#include <stdlib.h>

typedef struct node_type
{
    char key;
    struct node_type *left, *right;
}BSTNodeT;


BSTNodeT *createNode(char givenKey)
{
    BSTNodeT *p = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if(p)
    {
        p->key = givenKey;
        p->left = p->right = NULL;
    }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char key)
{
    if(root == NULL)
    {
        root = createNode(key);
    }
    else
    {
        if(key < root->key)
        {
            root->left = insertNode(root->left, key);
        }
        else if(key > root->key)
        {
            root->right = insertNode(root->right, key);
        }
        else
        {
            printf("\nNode with key = %c already exists\n", key);
        }
    }
    return root;
}

BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if(root == NULL)
    {
        return NULL;
    }
    for(BSTNodeT *p = root; p != NULL;)
    {
        if(givenKey == p ->key)
        {
            return p;
        }
        else if(givenKey < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }
    return NULL;
}

BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    if(node->left)
    {
        return findMin(node->left);
    }
    else
    {
        return node;
    }
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {
        return NULL;
    }
    if(node->right)
    {
        return findMax(node->right);
    }
    else
    {
        return node;
    }
}

BSTNodeT *delNode(BSTNodeT* node, char key)
{
    if(node == NULL)
    {
        printf("Element not found\n");
    }
    else if(key < node->key)
    {
        node->left = delNode(node->left, key);
    }
    else if(key > node->key)
    {
        node->right = delNode(node->right, key);
    }
    else
    {
        if(node->right && node->left)
        {
            BSTNodeT *temp = findMin(node->right);
            node -> key = temp->key;
            node->right = delNode(node->right, temp -> key);
        }
        else
        {
            BSTNodeT *temp = node;
            if(node->left == NULL)
            {
                node = node->right;
            }
            else if(node->right == NULL)
            {
                node = node -> left;
            }
            free(temp);
        }
    }
    return node;
}

void preorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        printf("%c\n", p->key);
        preorder(p->left);
        preorder(p->right);
    }
}

void inorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        inorder(p->left);
        printf("%c\n", p->key);
        inorder(p->right);
    }
}

void postorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        printf("%c\n", p->key);
    }
}

int main(char argc, char *argv[])
{
    BSTNodeT *currentRoot;
    currentRoot = NULL;
    FILE   *fi, *fo;
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "w");
    char command[10];
    while(fscanf(fi, "%s", command) != EOF)
    {
        if(command[0] == 'i') //insert node
        {
            if(currentRoot == NULL)
            {
                currentRoot = insertNode(NULL, command[1]);
            }
            else
            {
                insertNode(currentRoot, command[1]);
            }
        }
        else if(command[0] == 'd') //delete node
        {
            BSTNodeT *p;
            p = find(currentRoot, command[1]);
            delNode(p, command[1]);
        }
        else if(command[0] == 'f') //find node
        {
            find(currentRoot, command[1]);
        }
        else if(command[0] == 't') //traverse
        {
            if(command[1] == 'p')
            {
                preorder(currentRoot);
            }
            else if(command[1] == 'P')
            {
                postorder(currentRoot);
            }
            else if(command[1] == 'i')
            {
                inorder(currentRoot);
            }
        }
        else if(command[0] == 'g') //get minimum or maximum
        {
            if(command[1] == 'm')
            {
                findMin(currentRoot);
            }
            else if(command[1] == 'M')
            {
                findMax(currentRoot);
            }
        }
    }
    return 0;
}
