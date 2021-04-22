#include <stdio.h>
#include <stdlib.h>
///Notes
//I used a singly linked list just to review the notions
typedef struct node
{
    int data;
    struct node *next;
    int indegree;
}NodeT;
typedef struct header
{
    NodeT *first;
    NodeT *last;
}Header;
Header *createList()
{
    Header *p=(Header*)malloc(sizeof(Header));
    if(p==NULL) exit(1);
    else
    {
        p->first=NULL;
        p->last=NULL;
    }
    return p;
}
NodeT *createNode(int inf)
{
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    p->data=inf;
    p->next=NULL;
    p->indegree=0;
    return p;
}
int searchList(Header *ListPtr, int i)//searches the lit in order to not add duplicates
{
    NodeT *p=ListPtr->first;
    while(p!=NULL)
        {if(p->data==i+1) return 1;
        p=p->next;}
    return 0;
}
int interDegree(int **adjM,int i,int nr)//calculates the inner degree of each vertex
{
    int degree=0;
    for(int j=0;j<nr;j++)
    {
        if(adjM[j][i]==1) degree++;
    }
    return degree;
}
Header  *addElements(int **adjM, int nr)//just adds all the elements in a singly linked list by inserting them at the back
{
    Header *ListPtr;
    ListPtr=createList();
   NodeT *p;
   for(int i=0;i<nr;i++)
    {
        if(searchList(ListPtr,i)==0)
        {
            p=createNode(i+1);
            if(ListPtr->first==NULL)
            {
                ListPtr->first=ListPtr->last=p;
            }
            else{
            ListPtr->last->next=p;
            ListPtr->last=p;
            }
            p->indegree=interDegree(adjM,i,nr);
        }
    }
    return ListPtr;
}
Header *sort(Header *ListPtr,int **adjM,int *array,int size)//sorts the list using a bubble sort(swaps the info in each node) and it uses the data given(who is faster than who)
{
    int count,i,OK;
    if(ListPtr->first==NULL) return NULL;//no items in list
    if(ListPtr->first==ListPtr->last) return ListPtr;//only 1 element
    NodeT *p=ListPtr->first,*p1;
    while(p!=NULL)
    {
        p1=p->next;
        while(p1!=NULL)
        {
            if(p->indegree>=p1->indegree)
            {
                count=size*2;
                i=0;
                OK=1;
                while(count!=0)//checks if the pair is in the given info, if it is and the nodes have the same inner degree skips
                {
                    if(array[i]==p->data && array[i+1]==p1->data)
                    {
                        OK=0;
                        break;
                    }
                    i=i+2;
                    count=count-2;
                }
                if(OK==1)
                {
                   int temp=p->data;
                p->data=p1->data;
                p1->data=temp;
                temp=p->indegree;
                p->indegree=p1->indegree;
                p1->indegree=temp;
                }
            }
        p1=p1->next;
        }
    p=p->next;
    }
    return ListPtr;
}
void printList(Header *listPtr)//prints the singly linked list
{
    NodeT *p;
    p=listPtr->first;
    while(p!=NULL)
    {
        printf("%d ",p->data);
        p=p->next;
    }
}
int main()
{
    int nr;
    scanf("%d",&nr);
    int *array;//dinamically alocated array
    array=(int*)malloc(sizeof(int)*nr*2);//put all the elements in an array in order to create my adj matrix
    int ind1,ind2,index=0;
    for(int i = 0; i < nr; i++)
    {
        scanf("%d %d",&ind1,&ind2);
        array[index]=ind1;
        index++;
        array[index]=ind2;
        index++;
    }
    int max=array[0];//finding the max in order to know the dimensions of the adj matrix
    for(int i=1; i<index; i++)
    {
       if(array[i]>max) max=array[i];
    }
    int **adjM;////dinamically alocated matrix
    adjM=(int**)calloc(max,sizeof(int*));
    for(int i=0; i<max;i++)
        adjM[i]=(int*)calloc(max,sizeof(int));
    for(int i=0;i<index;i++)//filling the adj matrix
    {
        ind1=array[i];
        i++;
        ind2=array[i];
        adjM[ind1-1][ind2-1]=1;
    }
    Header *listPtr;
    listPtr=addElements(adjM,max);
    listPtr=sort(listPtr,adjM,array,nr);
    printList(listPtr);
    return 0;
}
