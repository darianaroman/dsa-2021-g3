/*Manage a hash table, using collision resolution by chaining, where the keys are student full names.
I/O description. Input:
i<name>
d<name>
f<name>
l
i<name>=insert <name>, d<name>=delete <name>, f<name>=find <name> in the table; l=list table contents.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define B 25
int f(char *key)
{
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
        if(key[i] != ' ')
        sum += key[ i ];
    return(sum % B);
}

typedef struct cell
{
    char key[60];
    struct cell *next;
} NodeT;

NodeT *BucketTable[B];

void initializeTable(NodeT *BucketTable[])
{
    for (int i = 0; i < B; i++)
        BucketTable[i] = NULL;
}

void fillNode(NodeT *p, char* key)
{
    strcpy(p->key, key);
    p->next = NULL;
}

NodeT* searchByKey(NodeT *BucketTable[], char* key)
{
    NodeT *p = (NodeT*) malloc(sizeof(NodeT));
    int h = f(key);
    p = BucketTable[h];
    while (p != NULL)
    {
        if (strcmp(key, p->key) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void deleteNode(NodeT* BucketTable[], NodeT *p, FILE* g)
{
    NodeT *q = (NodeT *) malloc(sizeof(NodeT));
    q = searchByKey(BucketTable, p->key);
    if(q == 0)
        fprintf(g, "\nThe %s node is not in the hash table\n", p->key);
    else
    {
        fprintf(g, "\n%s node is deleted\n", p->key);
        int h = f(p->key);
        BucketTable[h] = p->next;
        p->next = NULL;
        free(p);
    }
}
void insertRecord(NodeT* BucketTable[], char* key, FILE* g)
{
    NodeT *p = (NodeT *) malloc(sizeof(NodeT));
    if (p)
    {
        fillNode(p, key);
        int h = f(p->key);
        if (BucketTable[h] == NULL)
        {
            BucketTable[h] = p;
            p->next = NULL;
        }
        else
        {
            NodeT *q = (NodeT *) malloc(sizeof(NodeT));
            q = searchByKey(BucketTable, p->key);
            if (q == 0)
            {
                p -> next = BucketTable[h];
                BucketTable[h] = p;
            }
            //else
            //insertRecord(BucketTable, key);
        }
        fprintf(g, "\nNew record inserted\n");
    }
    else
        fprintf(g, "\nNew record cannot be inserted because of memory allocation error\n");
}

void listingHash(NodeT *BucketTable[], FILE* g)
{
    NodeT *p = (NodeT*) malloc(sizeof(NodeT));
    for (int i = 0; i < B; i++)
        if (BucketTable[ i ] != NULL)
        {
            fprintf(g, "\nBucket for hash value %d", i);
            p = BucketTable[i];
            while (p != NULL)
            {
                fprintf(g, "\n%s\n", p->key);
                p = p->next;
            }
        }
}
int main(int argc, char const **argv)
{
    FILE *f = fopen (argv[1], "r");
    FILE *g = fopen (argv[2], "w");
    char line[20];
    char x;
    initializeTable(BucketTable);
    while ((x = fgetc(f)) != EOF)
    {
        if(x == 'i')
        {
            fgetc(f);
            int i = 0;
            while ((f != EOF) && ((x = fgetc(f)) != '\n'))
                line[i++] = x;
            line[i] = '\0';
            fprintf(g, "\n%s", line);
            NodeT *p = (NodeT*)malloc(sizeof(NodeT));
            insertRecord(BucketTable, line, g);
        }
        else if(x == 'l')
        {
            listingHash(BucketTable, g);
            fgetc(f);
        }
        else if(x == 'd')
        {
            fgetc(f);
            int i = 0;
            while ((f != EOF) && ((x = fgetc(f)) != '\n'))
                line[i++] = x;
            line[i] = '\0';
            NodeT *p = (NodeT*) malloc (sizeof(NodeT));
            p = searchByKey(BucketTable, line);
            deleteNode(BucketTable, p, g);
        }
        else
        {
            fgetc(f);
            int i = 0;
            while ((f != EOF) && ((x = fgetc(f)) != '\n'))
                line[i++] = x;
            line[i] = '\0';
            NodeT *p = (NodeT*) malloc (sizeof(NodeT));
            p = searchByKey(BucketTable, line);
            if(!p)
                fprintf(g, "\n%s no\n", line);
            else
            {
                fprintf(g, "\n%s yes %d\n", p->key, p->next);
            }
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
