#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node_type
{
    int truck_id;
    char place;
    struct node_type *next;
}NodeT;

typedef struct
{
    int count;
    NodeT *first;
    NodeT *last;
}ListT;

ListT *createEmptyDLL()
{
    ListT *listPtr = (ListT *) malloc(sizeof(ListT));
    if (listPtr)
    {
        listPtr->count = 0;
        listPtr->first = NULL;
        listPtr->last = NULL;
        return listPtr;
    }
    printf("Not enough memory for list");
    exit(1);
}

NodeT *createNode(int key)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    if(p)
    {
        p->truck_id = key;
        p->place = 'X';
        p->next = NULL;
        return p;
    }
    printf("Not enough memory for node");
    return NULL;
}

int insertAtFront(int key, ListT *listPtr)
{
    //for placing trucks in garage
   NodeT *p = createNode(key);
   if(p)
   {
       p->next = listPtr->first;
       if(listPtr->count == 0)
       {
           listPtr->last = p;
       }
       listPtr->first=p;
       p->place = 'G';
       listPtr->count++;
       return 1;
   }
   printf("Error creating node and inserting it");
   return 0;
}

int insertAtRear(int key, ListT *listPtr)
{
    //for placing trucks on road
    NodeT *p = createNode(key);
    if(p)
    {
        p->next = NULL;
        if(listPtr->count == 0)
            listPtr->first = p;
        else
            listPtr->last->next=p;
        listPtr->last=p;
        p->place = 'R';
        listPtr->count++;
        return 1;
    }
    printf("Error creating node and inserting it at rear");
    return 0;
}

void deleteFirstNode(ListT *listPtr)
{
    NodeT *p = listPtr->first;
    listPtr->first = p->next;
    p->next = NULL;
    listPtr->count--;
    free(p);
}

void exitGarage(int key,ListT *listPtr)
{
    if(listPtr->first->place == 'G' && listPtr->first->truck_id == key)
    {
        deleteFirstNode(listPtr);
        insertAtRear(key,listPtr);
    }
     else
    {
         printf("Truck not in garage or not at exit!");
    }
}

void show(ListT *listPtr,char s) {
    if (s == 'R') {
        NodeT *p = listPtr->first;
        printf("R:");
        if (listPtr->last->place != 'R') {
            printf(" none");
            return;
        }
        while (p) {
            if (p->place == 'R')
                printf(" %d", p->truck_id);
            p = p->next;
        }
    } else if (s == 'G') {
        NodeT *p = listPtr->first;
        printf("G:");
        if (listPtr->first->place != 'G') {
            printf(" none");
            return;
        }
        while (p->place == 'G') {
            printf(" %d", p->truck_id);
        }
    }
}

int main()
{
    char line[20];
    int x;

    ListT *listPtr = createEmptyDLL();

    FILE *ifptr = fopen("input.txt", "r");
    if (ifptr == NULL)
    {
        printf("error: no input file!\n");
        return -1;
    }
    while (fgets(line, 20, ifptr) != NULL)
    {
        if (line[0] == 'S')
        {
            if (strchr("GgRr",line[2]) == NULL)
                printf("error: invalid list for %s\n", line);
            else
                show(listPtr,line[2]);
        }
        else if (strchr("0123456789",line[2]) == NULL)
            printf("error: invalid ID for %s\n", line);
        else
        {
            x = atoi(line+2);
            switch (line[0])
            {
                case 'R':
                    insertAtRear(x,listPtr);
                    break;
                case 'X':
                    exitGarage(x,listPtr);
                    break;
                case 'E':
                    insertAtFront(x,listPtr);
                    break;
                default:
                    printf("error: The only functions available are: S, R, X and E (also, no spaces are allowed at the beginning)\n");
            }
        }
    }
    return 0;
}
