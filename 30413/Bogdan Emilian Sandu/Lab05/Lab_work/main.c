#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char key;
    struct node *left, *right;
} BSTNodeT;

BSTNodeT *createN(char c)
{
    BSTNodeT *p;
    p=(BSTNodeT*)malloc(sizeof(BSTNodeT));
    if(p==NULL) exit(1);
    p->key=c;
    p->left=NULL;
    p->right=NULL;
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char c)
{
    if(root==NULL)
    {
        root=createN(c);
    }
    else
    {
        if(c<root->key)
            root->left=insertNode(root->left,c);
        else if(c>root->key)
            root->right=insertNode(root->right,c);
        else printf("already exists\n");
    }
    return root;
}
BSTNodeT *findMin(BSTNodeT *node)
{
    if(node==NULL)
        return NULL;
    if(node->left)
        return findMin(node->left);
    else
        return node;
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if(node==NULL)
        return NULL;
    if(node->right)
        return findMax(node->right);
    else
        return node;
}
BSTNodeT *find(BSTNodeT *root, char key)
{
    BSTNodeT *p;
    if(root==NULL)
    {
        return NULL;
    }
    p=root;
    while(p!=NULL)
    {
        if(p->key==key)
            return p;
        else
        {
            if(key<p->key) p=p->left;
            else p=p->right;
        }
    }
    return NULL;
}
BSTNodeT *deleteN(BSTNodeT *node, char c,char *s)
{
    FILE *out;
    if(node==NULL)
    {
        out=fopen(s,"a");
        fprintf(out,"Not found\n");
        fclose(out);
    }
    else if(c<node->key)
        node->left=deleteN(node->left,c,s);
    else if(c>node->key)
        node->right=deleteN(node->right,c,s);
    else
    {
        if(node->right!=NULL && node->left!=NULL)
        {
            BSTNodeT *temp=findMin(node->right);
            node->key=temp->key;
            node->right=deleteN(node->right,temp->key,s);
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
void preorder(BSTNodeT *p, char *s)
{
    FILE *out;
    if (p != NULL)
    {
        out=fopen(s,"a");
        fprintf(out,"%c ",p->key);
        fclose(out);
        preorder(p->left,s);
        preorder(p->right,s);
    }
}
void inorder(BSTNodeT *p, char *s)
{
    FILE *out;
    if (p != NULL)
    {
        inorder(p->left,s);
        out=fopen(s,"a");
        fprintf(out,"%c ",p->key);
        fclose(out);
        inorder(p->right,s);
    }
}
void postorder(BSTNodeT *p, char *s)
{
    FILE *out;
    if (p != NULL)
    {
        postorder(p->left,s);
        postorder(p->right,s);
        out=fopen(s,"a");
        fprintf(out,"%c ",p->key);
        fclose(out);
    }
}
void delTree(BSTNodeT *root)
{
    if(root!=NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }
}
int main(int argc,char *argv[])
{
    FILE *in,*out;
    char com[3];
    BSTNodeT *root=NULL,*p;
    in=fopen(argv[1],"r");
    if(in==NULL) exit(1);
    out=fopen(argv[2],"w");
    fclose(out);
    while(fscanf(in,"%s",com)==1)
    {
        switch(com[0])
        {
        case 'i':
            root=insertNode(root,com[1]);
            break;
        case 'd':
            deleteN(root,com[1],argv[2]);
            break;
        case 'f':
            out=fopen(argv[2],"a");
            p=find(root,com[1]);
            if(p!=NULL) fprintf(out,"Found node %c\n",p->key);
            else fprintf(out,"Not found\n");
            fclose(out);
            break;
        case 't':
            if(com[1]=='p')
            {
                preorder(root,argv[2]);
                out=fopen(argv[2],"a");
                fprintf(out,"\n");
                fclose(out);
            }
            if(com[1]=='P')
            {
                postorder(root,argv[2]);
                out=fopen(argv[2],"a");
                fprintf(out,"\n");
                fclose(out);
            }
            if(com[1]=='i')
            {
                inorder(root,argv[2]);
                out=fopen(argv[2],"a");
                fprintf(out,"\n");
                fclose(out);
            }
            break;
        case 'g':
            out=fopen(argv[2],"a");
            if(com[1]=='m')
            {
                p=findMax(root);
                if(p!=NULL)fprintf(out,"%c\n",p->key);
            }
            else if(com[1]=='M')
            {
                p=findMin(root);
                if(p!=NULL) fprintf(out,"%c\n",p->key);
            }
            fclose(out);
            break;
        }
    }
    return 0;
}
