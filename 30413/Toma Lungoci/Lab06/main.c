#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define X 4
typedef struct cell
{
    char key[60];
    struct cell *next;
}NodeT;



int hashFunction(char *key)
{
    int sum=0;
    for(int i=0; i<strlen(key); i++)
        sum += key[i];
    return (sum%X);
}


NodeT *createCell(char *key)
{
    NodeT *p=malloc(sizeof(NodeT));
    if(p)
    {
        strcpy(p->key, key);
        p->next=NULL;
        return p;
    }
    return NULL;
}

NodeT *find(char *key, NodeT *BucketTable[])
{
    int h=hashFunction(key);
    NodeT *p;
    p=BucketTable[h];
    while(p!=NULL)
    {
        if(strcmp(key, p->key)==0)
            return p;
        p=p->next;
    }
    return NULL;
}

void insertInTable (char *key, NodeT *BucketTable[], FILE *fout)
{
    NodeT *p=createCell(key);
    int h=hashFunction(p->key);
    if(BucketTable[h]==NULL)
    {
        BucketTable[h]=p;
        return;
    }
    NodeT *q=find(p->key, BucketTable);
    if(q==NULL)
    {
        p->next=BucketTable[h];
        BucketTable[h]=p;
    }
    else
    {
        fprintf(fout, "already in the table\n");
    }
}

void print(NodeT *BucketTable[], FILE *fout)
{
    int i;
    for(i=0; i< X; i++)
        if(BucketTable[i]!=NULL)
        {
            fprintf(fout, "Bucket for has value %d:\n", i);
            NodeT *p;
            p=BucketTable[i];
            while(p!=NULL)
            {
                fprintf(fout, "%s ", p->key);
                p=p->next;
            }
            fprintf(fout, "\n");
        }
}

void deleteName (NodeT *BucketTable[], char *key)
{
    int hf=hashFunction(key);
    NodeT *p=BucketTable[hf];
    NodeT *q=NULL;
    while(p!=NULL)
    {
        if(strcmp(p->key, key)==0)
            break;
        q=p;
        p=p->next;
    }
    if(q==NULL)
    {
        BucketTable[hf]= p->next;
        free(p);
    }
    else
    {
        if(p->next==NULL)
        {
            q->next=NULL;
            free(p);
        }
        else
        {
           q->next=p->next;
           free(p);
        }

    }
}

void readInput(FILE *fin, FILE *fout, NodeT *BucketTable[])
{
    char name[60];
    while (fscanf(fin, "%s", name)!=EOF)
    {
        if(name[0]=='i')
        {
            insertInTable(name+1, BucketTable, fout);
        }
        else if(name[0]=='d')
        {
            deleteName(BucketTable, name+1);
        }
        else if(name[0]=='l')
        {
            print(BucketTable, fout);
        }
        else
            fprintf(fout, "command not found");

    }
}
int main(int argc, char *argv[])
{
    NodeT *BucketTable[X];
    for(int i=0; i<X ;i++)
        BucketTable[i]=NULL;

    for(int i=1; i<argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    FILE *fin=fopen(argv[1], "r");
    FILE *fout=fopen(argv[2], "w");


    readInput(fin, fout, BucketTable);


    fclose(fin);
    fclose(fout);
    return 0;
}
