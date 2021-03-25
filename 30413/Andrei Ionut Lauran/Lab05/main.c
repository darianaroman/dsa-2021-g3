#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char key;
    struct node *left,*right;
}BSTNodeT;


BSTNodeT *createNode(char givenKey)
{
    BSTNodeT *p = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if(p!=0)
    {
        p->key=givenKey;
        p->left=p->right=NULL;
    }
    return p;
}

void preorder(BSTNodeT *p,FILE *file)
{
    fprintf(file,"%c",p->key);
    preorder(p->left,file);
    preorder(p->right,file);
}

void inorder(BSTNodeT *p,FILE *file)
{
    inorder(p->left,file);
    fprintf(file,"%c",p->key);
    inorder(p->right,file);
}

void postorder(BSTNodeT *p,FILE *file)
{
    postorder(p->left,file);
    postorder(p->right,file);
    fprintf(file,"%c",p->key);
}

BSTNodeT *findMin(BSTNodeT *root)
{
    if(root==NULL)
        return NULL;
    if(root->left)
        return findMin(root->left);
    else
        return root;
}

BSTNodeT *findMax(BSTNodeT *root)
{
    if(root==NULL)
        return NULL;
    if(root->right)
        return findMax(root->right);
    else
        return root;
}

BSTNodeT *insert(BSTNodeT *root,char givenKey,FILE *file)
{
    if(root == NULL)
        root=createNode(givenKey);
    else
    {
        if(strcmp(root->key,givenKey)<0)
            root->right = insert(root->right,givenKey,file);
        else if(strcmp(root->key,givenKey)>0)
            root->left = insert(root->left,givenKey,file);
        else
            fprintf(file,"\nNode with key %c already exists\n",givenKey);
    }
    return root;
}

BSTNodeT *find(BSTNodeT *root,char givenKey)
{
    if(root==NULL)
        return NULL;
    for(BSTNodeT *p = root; p!=NULL;)
    {
        if(strcmp(p->key,givenKey)==0)
            return p;
        else if(strcmp(p->key,givenKey)<0)
            p=p->left;
        else
            p=p->right;
    }
    return NULL;
}

BSTNodeT *delete(BSTNodeT *root,char givenKey,FILE *file)
{
    if(root==NULL)
        fprintf(file,"Element Not Found");
    else if(strcmp(givenKey,root->key)<0)
        root->left = delete(root->left,givenKey,file);
    else if(strcmp(givenKey,root->key)>0)
        root->right = delete(root->right,givenKey,file);
    else
    {
        if(root->left && root->right)
        {
            BSTNodeT *p = findMin(root->right);
            root->key = p->key;
            root->right = delete(root->right,p->key,file);
        }
        else
        {
            BSTNodeT *p = root;
            if(root->left==NULL)
                root = root->right;
            else if(root->right==NULL)
                root = root->left;
            free(p);
        }
    }
    return root;
}

int main(int *argc,char *argv[])
{
    FILE *f = fopen("argv[1]","r");
    FILE *g = fopen("argv[2]","w");
    BSTNodeT *root;
    BSTNodeT *p;
    char key[2];

    while(key[0]!='x')
    {
        fscanf(f, "%s", key);
        if (key[0] == 'i')
            insert(root, key[1], g);

        else if (key[0] == 'd')
            delete(root, key[1], g);

        else if (key[0] == 'f')
            find(root, key[1]);

        else if (key[0] == 't' && key[1] == 'p')
            preorder(root, g);

        else if (key[0] == 't' && key[1] == 'P')
            postorder(root, g);

        else if (key[0] == 't' && key[1] == 'i')
            inorder(root, g);

        else if (key[0] == 'g' && key[1] == 'm')
            p = findMin(root);

        else if (key[0] == 'g' && key[1] == 'M')
            p = findMax(root);
    }
    return 0;
}
