#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char key;
    //ElementType info;
    struct node_type *left, *right;
} BSTNodeT;

BSTNodeT *createNode(char givenKey)
{
    /* build node */
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
        p->key=givenKey;
        /* the info field should be filled in here */
        p->left = p-> right = NULL; /* leaf node */
    }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char key,FILE *f)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
    {
        root=createNode(key);
    }



    else
    {
        if (key<root->key)
            root->left = insertNode(root->left, key,f);
        else if (key>root->key)
            root->right = insertNode(root ->right, key,f);
        else
            fprintf(f,"\nNode with key = %c already exists\n", key);
    }
    return root;
}

BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if (root == NULL) return NULL; /* empty tree */
    for (BSTNodeT *p = root; p != NULL;)
    {
        if (givenKey==p->key) return p;
        else if (givenKey < p->key)
            p = p->left;
        else
            p = p->right;
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

BSTNodeT* delNode(BSTNodeT* node, char key,FILE *f)
{
    if(node == NULL)
    {
        fprintf(f,"Element Not Found");
    }
    else if(key < node->key)
    {
        // must be in left subtree
        node->left = delNode(node->left, key,f);
    }
    else if(key > node->key)
    {
        // must be in right subtree
        node->right = delNode(node->right, key,f);
    }
    else
    {
        // found node

        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            BSTNodeT *temp = findMin(node->right);
            node->key=temp->key;
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = delNode(node->right, temp->key,f);
        }
        else
        {

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
void preorder(BSTNodeT *p,FILE *f)
{
    if (p != NULL)
    {
        fprintf(f,"%c ",p->key);
        preorder(p->left,f);
        preorder(p->right,f);
    }
}
void inorder(BSTNodeT *p,FILE *f)
{
    if (p != NULL)
    {
        inorder(p->left,f);
        fprintf(f,"%c ",p->key);
        inorder(p->right,f);
    }
}
void postorder(BSTNodeT *p,FILE *f)
{
    if (p != NULL)
    {
        postorder(p->left,f);
        postorder(p->right,f);
        fprintf(f,"%c ",p->key);
    }
}

int main(int argc, char **argv )
{
    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");
    char string[3],b;

    int lines=0;
    b=fgetc(fin);
    while(b!=EOF)
    {
        if(b=='\n')
            lines++;
        b=fgetc(fin);
    }
    rewind(fin);
 //   printf("%d\n",lines);
    int i;
    BSTNodeT *root=NULL,*t;
    for(i=0; i<lines; i++)
    {

        fscanf(fin,"%s",string);
//        printf("%s\n",string);



        switch(string[0])
        {
        case 'i':
            if(root==NULL) root=insertNode(root,string[1],fout);
            else
                insertNode(root,string[1],fout);
            break;
        case 'd':

            delNode(root,string[1],fout);
            break;

        case 'f':
                if(find(root,string[1])!=NULL)
                fprintf(fout,"Key %c found\n",string[1]);
                else
                    fprintf(fout,"Key %c not found\n",string[1]);

                break;
        case 't':

            if(string[1]=='p')
            {
                fprintf(fout,"preorder:");
                preorder(root,fout);
                fprintf(fout,"\n");
            }
            else if(string[1]=='P')
            {
                fprintf(fout,"postorder:");
                postorder(root,fout);
                fprintf(fout,"\n");
            }
            else if(string[1]=='i')
            {
                fprintf(fout,"inorder:");
                inorder(root,fout);
                fprintf(fout,"\n");
            }

            else fprintf(fout,"Wrong instruction!\n");

            break;

        case 'g':
            if(string[1]=='m')
            {
                t=findMin(root);
                fprintf(fout,"Minimum node is %c\n",t->key);

            }

            else if(string[1]=='M')
            {
                 t=findMax(root);
                 fprintf(fout,"Maximum node is %c\n",t->key);
            }

            else printf("wrong instruction!");
            break;


        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}



