#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
  int key; /* an optional field identifying the data */
  /* other useful data fields */
  struct node *next; /* link to next node */
} NodeT;
typedef struct
{
  int count; /* an optional field */
  NodeT *first; /* link to the first node in the list */
  //NodeT *last; /* link to the last node in the list */
} ListT;
ListT *createEmptySLL()
{
	ListT *listPtr = (ListT*)malloc(sizeof(ListT));
	if (listPtr)
	{
		listPtr->count = 0; // list empty
		listPtr->first = NULL;
	}
	return listPtr;
}
NodeT *createSLLNode(int key)
{
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p)
    {
        // what is done here depends on the data stored at the node
        p->key = key; // assignment allowed as the key is of a primitive type
        p->next = NULL;
    }
    return p;
}
int isEmpty(ListT *listPtr)
{
    if(listPtr->count == 0 && listPtr->first == NULL)
        return 1;
    return 0;
}
int insertAtFront(ListT *listPtr, NodeT *p)
{
    if (listPtr)
    {
        // the list is non null
        p->next = listPtr->first;
        if (isEmpty(listPtr))
        {
            // p will be the sole node in the list
            //listPtr->last = p;
        }
        listPtr->first = p;
        listPtr->count++;
        return 1; // success
    }
    return 0; // failure
}
void isLoopPresent(ListT *myList)
{

    NodeT *slowPointer;
    NodeT *fastPointer;
    slowPointer = myList->first;
    fastPointer = myList->first;

    int loopFound = 0;

    while(fastPointer != NULL)
    {

        fastPointer = fastPointer->next->next;
        slowPointer = slowPointer->next;
        printf("%d %d\n", fastPointer->key, slowPointer->key);
        if(fastPointer->key == slowPointer->key)
        {
            loopFound = 1;
            // we need to break otherwise it will go on forever
            break;
        }
    }

    if(loopFound)
    {
        //move the slowPointer to the start of the list
        slowPointer = myList->first;

        while(slowPointer != fastPointer)
        {
            // prgressively moving both pointers one node at a time
            slowPointer = slowPointer->next;
            fastPointer = fastPointer->next;
        }
        printf("Start of loop is %d\n", slowPointer->key);
    }
    else
    {
        printf("No Loop Found");
    }
}
void printList(ListT *listPtr)
{
    if(isEmpty(listPtr))
        printf("Empty list\n");
    else
    {
        NodeT *r = listPtr->first;
        while(r != NULL)
        {
            printf("%d ", r->key);
            r = r -> next;
        }
    }
    printf("\n");
}
NodeT *find(ListT *listPtr, int givenKey)
{
    NodeT *p;
    p = listPtr->first;
    while ( p != NULL )
        if ( p->key == givenKey ) /* Note. This comparison does work for primitive types only */
        {
            return p; /* key found in cell p */
        }
        else
            p = p->next;
    return NULL; /* not found */
}
void purge(ListT *listPtr)
{
	NodeT *p;
	while ( listPtr->first != NULL )
	{
	  p = listPtr->first;
	  listPtr->first = listPtr->first->next;
	  free( p );
	}
	//listPtr->last = NULL;
	listPtr->count = 0;
}
main(int argc, char const *argv[])
{
    /*
    Creating a Linked List of eight nodes
    having a loop at (node 3)
    HEAD-->1-->2-->3-->4-->5
                   ^       |
                   |       v
                   8<--7<--6

    */
    //Head node pointing to first node of linked list
    ListT *myList = createEmptySLL();

    // creating a dependency in nodes by linking node to one another
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    for(int i = 8; i >= 1; i--)
    {
        p = createSLLNode(i);
        int x = insertAtFront(myList, p);
        if(x == NULL)
            printf("Could not insert new node %d", i);
    }
    printList(myList);
    p = find(myList, 8);
    p->next = find(myList, 3);// this line creates the loop
    //printf("%d\n", p->next->key);
    //calling method to evaluate
    isLoopPresent(myList);
    free(p);
    purge(myList);
    return 0;
}
