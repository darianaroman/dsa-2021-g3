#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 5

typedef struct node_type
{
    char name[100];

    struct node_type *next;
} NodeT;

NodeT *hashTable[B];

NodeT *createNode (char name[])
{
    NodeT *p = (NodeT*) malloc(sizeof(NodeT));
    strcpy(p->name, name);
    p->next = NULL;
    return p;
}

int hashFunction (char name[], int lenght)
{
    int a = 0, i;
    for (i = 0; i < lenght; i++) {
        a += name[i];
    }

    return (a % B);
}

int findName (NodeT *header, char name[])
{
    NodeT *p = header;
    while (p != NULL) {
        if ( !strcmp(p->name, name) ) {
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void deleteName (NodeT *header, char name[])
{
    NodeT *p = header;
    while ( strcmp(p->name, name) ) {
        p = p->next;
    }
    NodeT *q = p;
    while ( q->next != NULL ) {
        q = q->next;
    }

    strcpy(p->name, q->name);
    free(q);
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    char c;
    char command;
    char name[100];
    int n = 0, i, x = 0, hash;

    while (c != EOF) {
        c = fgetc(fileI);
        if(c == '\n') {
            n++;
        }
    }
    rewind(fileI);

    c = 'z';
    for (i = 0; i < n; i++) {
        command = fgetc(fileI);
        fprintf(fileO, "%c : ", command);
        x = 0;
        while (c != '\n') {
            c = fgetc(fileI);
            name[x] = c;
            x++;
        }
        x--;            /// x is now the lenght of the name
        name[x] = '\0';
        c = 'z';        /// c needs to be different from '\n'

        hash = hashFunction(name, x);
        printf("%d\n", hash);

        if (command == 'i') {
            if (hashTable[hash] == NULL) {
                hashTable[hash] = createNode(name);
            }
            else {
                NodeT* q = hashTable[hash];
                while (q->next != NULL) {
                    q = q->next;
                }
                q->next = createNode(name);
            }
            fprintf(fileO, "inserted %s\n", name);
        }
        else if (command == 'f') {
            if (findName(hashTable[hash], name)) {
                fprintf(fileO, "yes : index = %d\n", hash);
            }
            else {
                fprintf(fileO, "no\n");
            }
        }
        else if (command == 'd') {
            deleteName(hashTable[hash], name);
            fprintf(fileO, "deleted %s\n", name);
        }
        else {
            fprintf(fileO, "error! command unknown\n");
        }

    }
    return 0;
}
