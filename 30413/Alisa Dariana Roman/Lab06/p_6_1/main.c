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

NodeT *createNode (char *array)
{
    NodeT *p = (NodeT*) malloc (sizeof(NodeT));
    strcpy(p->name, &array);
    p->next = NULL;
    return p;
}

int hashFunction(char *array, int lenght)
{
    int i;
    int a = 0;
    for (i = 0; i < lenght; i++) {
        a += *(array + i);              /// a will be sum of all ASCII codes
    }
    printf("%d\n", a % B);

    return (a % B);

}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    char c;
    int countLines = 0;

    for (;;) {
        c = fgetc(fileI);
        if (c == EOF) {
            countLines++;
            break;
        }
        if(c == '\n') {
            countLines++;
        }
    }
    rewind(fileI);

    char array[100];
    int i;
    int aux;
    char *p;

    for (i = 0; i < countLines; i++) {
        fgets(array, 255, fileI);

        c = array[0];
        fprintf(fileO, "%c : ", c);
        p = &array[1];

        switch(c) {

        case 'i' :
            aux = hashFunction(p, strlen(array) - 2);
            if (hashTable[aux] == NULL) {
                hashTable[aux] = createNode(p);
            }
            else {
                NodeT *q = hashTable[aux];
                while(q->next != NULL) {
                    q = q->next;
                }
                q->next = createNode(p);
            }
            fprintf(fileO, "name was inserted\n");
            break;

        case 'd' :
            break;

        case 'f' :

            break;

        default :
            fprintf(fileO, "error! unknown comand");

        }
    }

    printf("%s", hashTable[1]->name);       /// i can't figure out what i'm doing wrong
                                            /// i'll try to figure out until tomorrow
    return 0;
}
