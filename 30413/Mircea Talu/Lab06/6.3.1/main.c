#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 4

typedef struct cell
{
    char key[60];
    struct cell *next;
}NodeT;

int hashFunction(char *key)
{
    int sum = 0;
    for(int i = 0; i < strlen(key); i++)
        sum = sum + key[i];
    return (sum % B);
}


NodeT *createCell(char *key)
{
    NodeT *p = malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->key, key);
        p->next = NULL;
        return p;
    }
    return NULL;
}

NodeT *find(char *key, NodeT *BucketTable[])
{
    int hK = hashFunction(key);
    NodeT *p;
    p = BucketTable[hK];
    while(p != NULL)
    {
        if(strcmp(key, p->key) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void insertInTable(char *key, NodeT *BucketTable[], FILE *out_file)
{
    NodeT *p = createCell(key);
    int h = hashFunction(p->key);
    if(BucketTable[h] == NULL)
    {
        BucketTable[h] = p;
        return;
    }
    NodeT *q = find(p->key, BucketTable);
    if(q == NULL)
    {
        p->next = BucketTable[h];
        BucketTable[h] = p;
    }
    else
    {
        fprintf(out_file, "already exists\n");
    }
}

void print(NodeT *BucketTable[], FILE *out_file)
{
    int i;
    for(i = 0; i < B; i++)
        if(BucketTable[i] != NULL)
        {
            fprintf(out_file, "%d", i);
            NodeT *p;
            p = BucketTable[i];
            while(p != NULL)
            {
                fprintf(out_file, "%s", p->key);
                p = p->next;
            }
            fprintf(out_file, "\n");
        }
}

void deleteName (NodeT *BucketTable[], char *key)
{
    int hF = hashFunction(key);
    NodeT *p = BucketTable[hF];
    NodeT *q = NULL;
    while(p != NULL)
    {
        if(strcmp(p->key, key) == 0)
            break;
        q = p;
        p = p->next;
    }
    if(q == NULL)
    {
        BucketTable[hF] = p->next;
        free(p);
    }
    else
    {
        if(p->next == NULL)
        {
            q->next = NULL;
            free(p);
        }
        else
        {
           q->next = p->next;
           free(p);
        }
    }
}

int main(int argc, char *argv[])
{
    NodeT *BucketTable[B];
    for(int i = 0; i < B; i++)
        BucketTable[i] = NULL;

    for(int i = 1; i < argc; i++)
    {
        printf("%s \n", argv[i]);
    }
    FILE *in_file = fopen(argv[1], "r");
    FILE *out_file = fopen(argv[2], "w");
    char txt[60];
    while (fscanf(in_file, "%s", txt) != EOF)
    {
        if(txt[0] == 'i')
        {
            insertInTable(txt + 1, BucketTable, out_file);
        }
        else
            if(txt[0] == 'd')
            {
                deleteName(BucketTable, txt + 1);
            }
            else
                if(txt[0] == 'l')
                {
                    print(BucketTable, out_file);
                }
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}
