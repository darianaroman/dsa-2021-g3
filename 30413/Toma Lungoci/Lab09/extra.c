#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
}NodeT;

typedef struct{
    NodeT *first;
    NodeT *last;
    char name;
}StackH;

NodeT *createNode (int givenkey){
    NodeT *p;
    p=(NodeT *)malloc(sizeof(NodeT));
    p->key=givenkey;
    p->next=NULL;
    return p;
}

void push(StackH *peg, NodeT *p)
{
    if(peg->first==NULL)
    {
        peg->first=p;
        peg->last=p;
    }
    else
    {
        peg->last->next=p;
        peg->last=p;
    }
}
void printPegs (StackH *peg, FILE *fo)
{
    fprintf(fo, "%c: ", peg->name);
    if(peg->first==NULL)
    {
        fprintf(fo, "Empty peg!");
    }
    else
    {
        NodeT *p;
        p=peg->first;
        while(p!=NULL)
        {
            fprintf(fo, "%d ", p->key);
            p=p->next;
        }
    }
    fprintf(fo, "\n");
}

void moveFromTo (StackH *from, StackH *to, FILE *fo)
{
    if(from->first==NULL)
    {
        fprintf(fo, "impossible move!");
        exit(1);
    }
    else
    {
        NodeT *p=from->last;
        push(to, p);
        NodeT *q=from->first;
        NodeT *q1=NULL;
        while(q->next!=NULL)
        {
            q1=q;
            q=q->next;
        }
        if(q1==NULL)
        {
            from->first=from->last=NULL;
        }
        else
        {
            q1->next=NULL;
            from->last=q1;
        }
    }
}

void hanoi(int n, StackH *A, StackH *B, StackH *C, FILE *fo)
{
    if(n>0)
    {
        hanoi(n-1, A, C, B, fo);
        moveFromTo(A, C, fo);
        printPegs(A, fo);
        printPegs(B, fo);
        printPegs(C, fo);
        fprintf(fo, "\n");
        hanoi(n-1, B, A, C, fo);
    }

}

int main(int argc, char *argv[])
{
    FILE *fi, *fo;
    fi=fopen(argv[1], "r");
    fo=fopen(argv[2], "w");

    StackH *A=(StackH *)malloc(sizeof(StackH));
    A->first=A->last=NULL;
    A->name='A';
    StackH *B=(StackH *)malloc(sizeof(StackH));//initialized the 3 pegs, header cells for the stacks
    B->first=B->last=NULL;
    B->name='B';
    StackH *C=(StackH *)malloc(sizeof(StackH));
    C->first=C->last=NULL;
    C->name='C';

    printf(" %c", A->name);
    int n, i;
    fscanf(fi, "%d", &n);//read from input the number of disks we need to move
    printf("%d", n);

    for(i=n; i>=1; i--)
    {
        NodeT *p;
        p=createNode(i);
        push(A, p);
    }

    printf("%d %d ", A->first->key, A->last->key);
    printPegs(A, fo);
    printPegs(B, fo);
    printPegs(C, fo);

    hanoi(n, A, B, C, fo);
    fclose(fi);
    fclose(fo);
    return 0;
}
