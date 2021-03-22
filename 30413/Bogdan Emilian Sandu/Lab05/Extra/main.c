#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
typedef struct node
{
    char exp[30];
    struct node *left, *right;
}NodeT;
typedef struct stackN
{
    struct stackN *next;
    NodeT *tn;//tree node
}StackN;
typedef struct stack
{
    StackN *bottom;//bottom ptr
    StackN *top;//top ptr
    int nr;//count of elements
}StackT;

StackN *createSN(NodeT *m)
{
    StackN *p;
    p=(StackN*)malloc(sizeof(StackN));
    if(p==NULL) exit(1);
    p->tn=m;
    p->next=NULL;
    return p;
}

NodeT *createNode(char *c)
{
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p==NULL) exit(1);
    strcpy(p->exp,c);
    p->left=NULL;
    p->right=NULL;
    return p;
}
StackT *createEmptyS()
{
    StackT *p;
    p=(StackT*)malloc(sizeof(StackT));
    if(p==NULL) exit(1);
    p->bottom=NULL;
    p->top=NULL;
    p->nr=0;
    return p;
}
void pushS(StackT *stackPtr,NodeT *p)
{
    StackN *m=createSN(p);
    if(stackPtr->nr==0)
        {
            stackPtr->top=stackPtr->bottom=m;
            m->next=NULL;
        }
    else
        {
            m->next=stackPtr->top;
            stackPtr->top=m;
        }
    stackPtr->nr++;
}
StackN *popS(StackT *stackPtr)
{
    StackN *p;
    p=stackPtr->top;
    if(stackPtr->nr==0) return NULL;
    else if(stackPtr->nr==1)
        stackPtr->top=stackPtr->bottom=NULL;
    else
        stackPtr->top=stackPtr->top->next;
    return p;
}
bool isOp(char *c)//verifica daca e operator
{
    if((c[0]=='+' || c[0]=='-' || c[0]=='*' || c[0]=='/') && isdigit(c[1])==0) return true;
    else return false;
}
char *revereS(char *s)//reverseaza ordinea cuvintelor
{
    char *p;
    int len=strlen(s);
    char v1[100];
    char *v;
    v=(char*)malloc(100*sizeof(char));
    strcpy(v,"");
    p=strtok(s," ");
    while(p!=NULL)
    {
        strcpy(v1,p);
        strcat(v1," ");
        strcat(v1,v);
        strcpy(v,v1);
        p=strtok(NULL," ");
    }
    v[len]='\0';
    return v;
}
NodeT *createTree(char *s)
{
    NodeT *root,*nd;
    StackT *stackPtr=createEmptyS();
    StackN *m,*n;
    char *word,revS[100];
    strcpy(revS,revereS(s));
    word=strtok(revS," ");
    while(word!=NULL)
    {
        if(isOp(word)==false)
    {
        nd=createNode(word);
        pushS(stackPtr,nd);
    }
    else
    {
        m=popS(stackPtr);
        n=popS(stackPtr);
        nd=createNode(word);
        nd->left=n->tn;
        nd->right=m->tn;
        pushS(stackPtr,nd);
        free(m);
        free(n);
    }
    word=strtok(NULL," ");
    }
    root=nd;
    free(stackPtr);
    return root;
}
void postfix(NodeT *root)
{
    if(root==NULL) return;
    postfix(root->left);
    postfix(root->right);
    printf("%s ",root->exp);
}
void prefix(NodeT *root)
{
    if(root==NULL) return;
    printf("%s ",root->exp);
    prefix(root->left);
    prefix(root->right);
}
void inorder(NodeT *root)
{
    if(root==NULL) return;
    inorder(root->left);
    printf("%s ",root->exp);
    inorder(root->right);
}
void delTree(NodeT *root)
{
    if(root!=NULL)
    {
        delTree(root->left);
        delTree(root->right);
        free(root);
    }

}

int main()
{
    char s[105];
    NodeT *root;
    scanf("%[^\n]",s);
    root=createTree(s);
    postfix(root);
    printf("\n");
    inorder(root);
    printf("\n");
    prefix(root);
    delTree(root);
    return 0;
}
