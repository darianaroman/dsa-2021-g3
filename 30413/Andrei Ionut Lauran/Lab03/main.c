#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    int apparitions;
    char word[20];
    struct node_type *next;
    struct node_type *prev;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptyDLList()
{
    ListT *listPtr = (ListT*)malloc(sizeof(ListT));
    if(listPtr)
    {
        listPtr->count = 0;
        listPtr->first = NULL;
        listPtr->last = NULL;
        return listPtr;
    }
    printf("Not enough memory for creating the list");
    return 0;
}

NodeT *createNode(char *word,ListT *listPtr)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(listPtr)
    {
        if(p)
        {
            p->apparitions = 1;
            strcpy(p->word,word);
            p->next = NULL;
            p->prev = NULL;
            return p;
        }
        printf("Not enough memory for creating the node");
        exit(1);

    }
    printf("The list is not created");
    return 0;
}

void sortList(ListT *listPtr)
{
    if(listPtr->count==0)
    {
        printf("Can't sort. List empty");
        return;
    }
    if(listPtr->count==1)
    {
        printf("Only 1 element in list.Nothing to sort");
        return;
    }
    NodeT *p1 = listPtr->first;
    NodeT *p2;
    while(p1->next != NULL)
    {
        p2=p1->next;
        while(p2->next!=NULL)
        {
            if (stricmp(p1->word, p2->word) > 0)
            {
                char word_1[20], word_2[20];
                int apparitions1, apparitions2;
                apparitions1 = p1->apparitions;
                apparitions2 = p2->apparitions;
                strcpy(word_1, p1->word);
                strcpy(word_2, p2->word);
                p1->apparitions = apparitions2;
                strcpy(p1->word, word_2);
                p2->apparitions = apparitions1;
                strcpy(p2->word, word_1);
            }
            p2 = p2->next;
        }
        p1 = p1->next;
    }
}

NodeT *find(char *givenWord,ListT *listPtr)
{
    NodeT *p = listPtr->first;
    while(p!=NULL)
    {
        if(stricmp(p->word,givenWord)==0)
            return p;
        p=p->next;
    }
    return NULL;
}

void insertAtRear(char *word,ListT *listPtr)
{
    NodeT *p = createNode(word,listPtr);
    if(p)
    {
        NodeT *p2 = find(word,listPtr);
        if(p2==NULL)
        {
            p->next = NULL;
            if (listPtr->count == 0)
            {
                listPtr->first = p;
                listPtr->last = p;
            }
            else
            {
                listPtr->last->next = p;
                p->prev = listPtr->first;
                listPtr->last = p;
            }
            listPtr->count++;
        }
        else
        {
            p2->apparitions++;
            free(p);
        }
    }
    else
        printf("Node not inserted");
}

void printList(ListT *listPtr)
{
    NodeT *p = listPtr -> first;
    while(p!=NULL)
    {
        printf("%s:%d\n", p->word, p->apparitions);
        p = p->next;
    }
}

void purge(ListT *listPtr)
{
    NodeT *p;
    while (listPtr->first != NULL)
    {
        p = listPtr->first;
        listPtr->first = listPtr->first->next;
        free(p);
    }
    listPtr->last=NULL;
    listPtr->count=0;
    free(listPtr);
}

int main()
{
    FILE *f = fopen("input.txt", "r");
    if(f == NULL)
    {
        printf("File not opened\n");
    }
    char line[20];
    ListT *listPtr = createEmptyDLList();
    while(fscanf(f,"%s",line) != EOF)
    {
        insertAtRear(line,listPtr);
    }
    sortList(listPtr);
    printList(listPtr);
    purge(listPtr);
    return 0;
}