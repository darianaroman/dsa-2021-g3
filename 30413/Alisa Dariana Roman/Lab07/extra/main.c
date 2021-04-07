#include <stdio.h>
#include <stdlib.h>
#define NR_NODES 20

typedef struct node_type
{
    int id;
    struct node_type *next;
} Node;

typedef struct list_type
{
    int count;
    Node *first;
    Node *last;
} List;

List *adjList[NR_NODES];
int inDegree[NR_NODES];

Node *createNode (int id)
{
    Node *p = (Node*) malloc (sizeof(Node));
    p->id = id;
    p->next = NULL;
    return p;
}

List *createList ()
{
    List *listPtr = (List*) malloc(sizeof(List));
    if (listPtr) {
        listPtr->count = 0;
        listPtr->first = listPtr->last = NULL;
    }
    return listPtr;
}

int isEmpty(List *listPtr)
{
    if (listPtr->count == 0) {
        return 1;
    }
    return 0;
}

int insertAtRear(List *listPtr, Node *p)
{
	if (listPtr) {
		if (isEmpty(listPtr)) {
			listPtr->first = p;
		}
		else {
			listPtr->last->next = p;
		}
		listPtr->last = p;
		listPtr->count++;
		return 1;
	}
	return 0;
}

int deleteFirst(List *listPtr)
{
    Node *p;
    int id;
    if ( listPtr->first != NULL ) {
        p = listPtr->first;
        id = p->id;
        listPtr->first = listPtr->first->next;
        free( p );
        listPtr->count--;
        if ( listPtr->first == NULL ) {
            listPtr->last = NULL;
        }
        return id;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    int n,  i, max = 0;
    int head, tail;

    fscanf(fileI, "%d", &n);
    for (i = 0; i < n; i ++) {
        fscanf(fileI, "%d %d", &tail, &head);       /// tail > head ; tail -> head

        if ( adjList[tail] == NULL ) {
            adjList[tail] = createList();
        }
        if ( !insertAtRear(adjList[tail], createNode(head)) ) {
            fprintf(fileO, "error");
        }

        inDegree[head]++;

        if (head > max) {
            max = head;
        }
        if (tail > max) {
            max = tail;
        }                       /// I use max to find out how many nodes we have
    }

    List *queue = createList();
    for (i = 1; i <= max; i++) {     /// initialize queue with nodes that have inDeg = 0
        if ( inDegree[i] == 0 ) {
            if ( !insertAtRear(queue, createNode(i)) ) {
                fprintf(fileO, "error");
            }
        }
    }

    int outID;
    Node *outNode;

    while (queue->count > 0) {
        outID = deleteFirst(queue);     /// deleteFirst(queue) deletes the first node in the queue and returns its id
        fprintf(fileO, "%d -> ", outID);

        if (adjList[outID] != NULL) {

            outNode = adjList[outID]->first;

            while (outNode != NULL) {   /// going through the adj list of the deleted node and decreasing the inDegree accordingly
                inDegree[outNode->id]--;
                if (inDegree[outNode->id] == 0) {   /// if inDegree == 0 add to queue
                    if ( !insertAtRear(queue, createNode(outNode->id)) ) {
                        fprintf(fileO, "error");
                    }
                }
                outNode = outNode->next;
            }
        }
    }
    return 0;
}
