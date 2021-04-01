#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 20
typedef struct cell
{
    char key[60];
    struct cell *next;
} NodeT;

NodeT *BucketTable[B];

int f(char *key)
{
    int sum, len;
    sum = 0;
    len = strlen(key);
    for (int i = 0; i < len; i++)
    sum += key[ i ];
    return(sum % B);
}

void init(NodeT *BucketTable[])
{
    for (int i = 0; i < B; i++)
    BucketTable[i] = NULL;
}

NodeT *find(NodeT *BucketTable[], char *key)
{
    int h;
    NodeT *p;
    h = f(key);
    p = BucketTable[h];
    while (p != NULL)
    {
    if (strcmp(key, p->key) == 0)
    return p;
    p = p->next;
    }
    return NULL;
}

void fillNode(NodeT *p, char key[])
{
    strcpy(p->key, key);
}

void insert(NodeT *BucketTable[], char key[])
{
    NodeT *q;
    NodeT *p = (NodeT *) malloc(sizeof(NodeT));
    int h;
    if (p)
    {
        fillNode(p, key);
        h = f(p->key);
        if (BucketTable[h] == NULL)
        {
            BucketTable[ h ] = p;
            p->next = NULL;
        }
    }
    else {
        q = find(BucketTable, p->key);
        if (q == 0)
        {
            p -> next = BucketTable[ h ];
            BucketTable[ h ] = p;
        }
    }
}

void deleteNode(NodeT *BucketTable[], char key[])
{
    int h;
    NodeT *q;
    q = find(BucketTable, key);
    if(q != NULL) {
        h = f(q->key);
        BucketTable[h] = q->next;
        //p->next = NULL;
        free(q);
        printf("the node was deleted\n");
    }
    else printf("the node is not in the hash table\n");


}

void showNode(NodeT *p)
{
    printf("%s\n", p->key);
}

void listing(NodeT *BucketTable[])
{
    int i;
    NodeT *p;
    for (i = 0; i < B; i++)
    if (BucketTable[ i ] != NULL)
    {
        printf("Bucket for hash value %d\n", i);
        p =BucketTable[ i ];
        while (p != NULL)
        {
            showNode(p);
            p = p->next;
        }
    }
}

int main()
{
    char c;
    init(BucketTable);
    FILE *f = fopen("in.txt", "r");

    while((c = fgetc(f)) != EOF)
    {
        int i = 0, len;
        char instr[20] = " ";
        char name[25] = " ";
        NodeT *q;

        while((c != '\n')) {
            instr[i++] = c;
            c= fgetc(f);
        }
        instr[i] = NULL;

        //SELECTING THE NAME
        len = strlen(instr);
        for(i = 2; i < len; i++)
            name[i-2] = instr[i];
            name[i-1] = NULL;
        //EXECUTING THE INSTRUCTIONS
        if(instr[0] == 'i')
            {
                insert(BucketTable, name);

            }
        else if(instr[0] == 'f')
            {
                q = find(BucketTable, name);
                if(q != 0) printf("the node with key %s is in the hash table\n", name);
                else printf("the node with key %s is not in the hash table\n", name);
            }
        else if (instr[0] == 'l')
             listing(BucketTable);
        else if (instr[0] == 'd')
             deleteNode(BucketTable, name);

    }
    return 0;
}
