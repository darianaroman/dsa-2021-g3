#include <stdlib.h>
#include <stdio.h>

typedef struct node_type
{
    char key;
    struct node_type *left;
    struct node_type *right;
}NodeT;

NodeT *createNode(char key)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->key = key;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    else
        printf("Not enough memory for creating node");
    return NULL;
}

NodeT *findMin(NodeT *root)
{
    if(root == NULL)
        return NULL;
    while(root->left)
        root = root->left;
    return root;
}

NodeT *findMax(NodeT *root)
{
    if(root == NULL)
        return NULL;
    while(root->right)
        root = root->right;
    return root;
}

void insertNode(NodeT *root,char givenKey)
{
    NodeT *p = createNode(givenKey);
    if(root == NULL)
   {
       root = p;
        return;
   }
    NodeT *q = root;
    for(; ;)
    {
        if(q->key > givenKey)
        {
            if (q->right == NULL)
            {
                q->right = p;
                return;
            }
            q = q->right;
        }
        else if(q->key < givenKey)
        {
            if(q->left == NULL)
            {
                q->left = p;
                return;
            }
            q = q->left;
        }
        else
            free(p);
    }
}

NodeT *insertNodeRec(NodeT *root,char givenKey)
{
    if(root == NULL)
        root = createNode(givenKey);
    else
    {
        if(root->key > givenKey)
            root->left = insertNodeRec(root->left, givenKey);
        else
            if(root->key < givenKey)
               root->right = insertNodeRec(root->right,givenKey);
            else
                printf("\nCan't insert.Node with key %c already exists\n",givenKey);
    }
    return root;
}

NodeT *find(NodeT *root,char givenKey)
{
    if(root == NULL)
    {
        return NULL;
    }
    NodeT *p = root;
    while(p)
    {
        if (p->key == givenKey)
            return p;
        else if (p->key > givenKey)
            p = p->left;
        else
            p = p->right;
    }
    return NULL;
}

NodeT *deleteNode(NodeT *root, char givenKey)
{
    if(root == NULL)
        printf("Can't delete. Element not found");
    else if(givenKey < root->key)
        root->left = deleteNode(root->left,givenKey);
    else if(givenKey > root->key)
        root->right = deleteNode(root->right,givenKey);
    else
    {
        if(root->right && root->left)
        {
            NodeT *temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,temp->key);
        }
        else
        {
            NodeT *temp = root;
            if(root->left == NULL)
                root = root->right;
            else if(root->right == NULL)
                root = root->left;
            free(temp);
        }
    }
    return root;
}

void preorder(NodeT *root,FILE *file)
{
    if(root)
    {
        fprintf(file,"%c ",root->key);
        preorder(root->left,file);
        preorder(root->right,file);
    }
}

void inorder(NodeT *root,FILE *file)
{
    if(root)
    {
        inorder(root->left,file);
        fprintf(file,"%c ",root->key);
        inorder(root->right,file);
    }
}

void postorder(NodeT *root,FILE *file)
{
    if(root)
    {
        postorder(root->left,file);
        postorder(root->right,file);
        fprintf(file,"%c ",root->key);
    }
}

int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1],"r");
    FILE *g = fopen(argv[2],"w");
    char line[3];
    NodeT *root;
    while(fgets(line,3,f)!=NULL)
    {
        if(line[0] == 'i')
        {
            insertNodeRec(root, line[1]);
        }
        else if(line[0] == 'd')
        {
            deleteNode(root, line[1]);
        }
        else if(line[0] == 'f')
        {
            NodeT *p = find(root,line[1]);
            if(p != NULL)
                fprintf(f,"\nKey %c found!\n",p->key);
            else
                fprintf(f,"\nKey %c not found\n",p->key);
        }
        else if(line[0] == 't')
        {
            if(line[1] == 'p')
                preorder(root,g);
            else if(line[1] == 'P')
                postorder(root,g);
            else if(line[1] == 'i')
                inorder(root,g);
        }
        else if(line[0] == 'g')
        {
            if(line[1] == 'm')
            {
                NodeT *p = findMin(root);
                fprintf("\nMinimum is %c\n",p->key);
            }
            else if(line[1] == 'M')
            {
                NodeT *p = findMax(root);
                fprintf("\nMaximum is %c\n",p->key);
            }
        }
    }
    return 0;
}