#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char key;
    struct node *left, *right;
}BSTNodeT;

BSTNodeT *createBSTNode (char key)
{
    BSTNodeT *p=(BSTNodeT *)malloc(sizeof(BSTNodeT));
    if(p)
    {
        p->key=key;
        p->left=p->right=NULL;
        return p;
    }
}

BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->left) /* Go to the left sub tree to find the min element */
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

BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if (root == NULL) return NULL; /* empty tree */
    for (BSTNodeT *p = root; p != NULL;)
    {
        if (givenKey == p->key) return p;
        else if (givenKey < p->key) p = p->left;
        else p = p->right;
    }
    return NULL; /* not found */
}

BSTNodeT *insertNode(BSTNodeT *root, char key, FILE *fo)
{
    if(root==NULL)
    {
        root=createBSTNode(key);
    }
    else
    {
        if(key <root->key)
        {
            root->left=insertNode(root->left, key, fo);
        }
        else if(key>root->key)
        {
            root->right=insertNode(root->right, key, fo);
        }
        else
            fprintf(fo, "already exists");
    }
    return root;
}

BSTNodeT *delNode (BSTNodeT *node, char key)
{
    if(node==NULL)
    {
        printf("element not found");
    }
    else if(key<node->key)
    {
        node->left =delNode(node->left, key);
    }
    else if(key>node->key)
    {
        node->right=delNode(node->right, key);
    }
    else
    {
        if(node->left && node->right)
        {
            BSTNodeT *temp = findMin(node->right);//replacing with the minimum from the right subtree
            node->key=temp->key;
            node->right=delNode(node->right, temp->key);
        }
        else
        {
            BSTNodeT *temp=node;
            if(node->left==NULL)
                node=node->right;
            else if(node->right==NULL)
                node=node->left;
            free(temp);
        }
    }
    return node;
}
void preorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        fprintf(fo, "%c ", p->key);
        preorder(p->left, fo);
        preorder(p->right, fo);
    }

}
void inorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        inorder(p->left, fo);
        fprintf(fo, "%c ", p->key);
        inorder(p->right, fo);
    }

}
void postorder(BSTNodeT *p, FILE *fo)
{
    if (p != NULL)
    {
        postorder(p->left, fo);
        postorder(p->right, fo);
        fprintf(fo, "%c ", p->key);
    }

}

void readData(FILE *fi,FILE *fo, BSTNodeT *root)
{
    char command[2];
    while(fscanf(fi, "%s ", command)!=EOF)
    {

        if(command[0]=='i')
        {
            if(root==NULL)
                root=insertNode(root, command[1], fo);
            else
                insertNode(root, command[1], fo);
        }
        else if(command[0]=='d')
        {
            delNode(root, command[1]);
        }
        else if(command[0]=='f')
        {
            if(find(root, command[1])!=NULL)
                fprintf(fo, "found!\n");
            else
                fprintf(fo, "not found:(\n");
        }
        else if(command[0]=='t')
        {
            if(command[1]=='p')
                preorder(root, fo);
            else if(command[1]=='P')
                postorder(root, fo);
            else
                inorder(root, fo);
        }
        else if(command[0]=='g')
        {
            if(command[1]=='m')
            {
               BSTNodeT*q= findMin(root);
               fprintf(fo, "min: %c\n", q->key);
            }
            else if(command[1]=='M')
            {
                BSTNodeT*q=findMax(root);
                fprintf(fo, "max: %c\n", q->key);
            }

        }
        else
            fprintf(fo, "command not found\n");
    }
}


int main(int argc, char *argv[])
{
    FILE *fi, *fo;
    fi=fopen(argv[1], "r");
    fo=fopen(argv[2], "w");
    for(int i=1; i<argc; i++)
    {
        printf("%s ", argv[i]);//check if read correctly
    }
    BSTNodeT *root=NULL;
    readData(fi,fo, root);
    fclose(fi);
    fclose(fo);
    printf("end");
    return 0;
}
