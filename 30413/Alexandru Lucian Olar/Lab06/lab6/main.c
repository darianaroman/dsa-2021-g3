#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 20

typedef struct N
{
    char key[60];
    struct N* pnext;
} Node;

Node* createnode(char *data)
{
    Node *p;
    p=(Node* )malloc(sizeof(Node));
    if(p)
    {
        strcpy(p->key,data);
        p->pnext= NULL;
    }
    return p;
}

int f(char *key)
{
    int i,sum,len;
    sum=0;
    len=strlen(key);
    for(i=0; i<len; i++)
    {
        sum=sum+key[i];
    }
    return (sum%B);
}

void insert(Node* HTable[B], char* data)
{
    Node* p;
    p=createnode(data);
    int h=f(data);
    p->pnext=HTable[h];
    HTable[h]=p;
}

FILE *fin, *fout;

void listHashTable(Node* HTable[B], FILE *fout)
{
    Node *p = NULL;
    int i;
    for(i = 0; i < B; i++)
    {
        p = HTable[i];
        fprintf(fout,"%d: ", i);
        while(p != NULL)
        {
            fprintf(fout,"%s", p->key);
            p = p->pnext;
        }
        fprintf(fout,"\n");
    }
    fprintf(fout,"\n");
}

int find(Node* HTable[B], char* data)
{
    int h=f(data);
    Node* p;
    p=HTable[h];
    while(p != NULL)
    {
        if(strcmp(p->key, data) == 0)
            return h;
        p = p->pnext;
    }
    return 0;
}

void deleteFromHTable(Node *HTable[B], char *data)
{
    int h = f(data);
    Node *p = NULL;
    p = HTable[h];
    Node *temp = NULL;
    if(strcmp(p->key, data) == 0)
    {
        HTable[h] = p->pnext;
        free(p);
    }
    else
    {
        while(p != NULL)
        {
            if(strcmp(p->key, data) == 0)
            {
                temp->pnext = p->pnext;
                free(p);
            }
            temp = p;
            p = p->pnext;
        }
    }
}

int main()
{
    FILE *fin,*fout;
    fin=fopen("date.in","r");
    fout=fopen("date.out","w");
    if(fin == NULL)
    {
        perror("not found");
        exit(-1);
    }
    if(fout == NULL)
    {
        perror("not found");
        exit(-1);
    }
    int i;
    Node* HTable[B];
    for (i = 0; i < B; i++)
        HTable[i] = NULL;

    char cmd[10];
    char c;
    while( fscanf(fin,"%s", cmd) != EOF)
    {
        c=cmd[0];
        strcpy(cmd,cmd+1);
        if( c == 'i')
            insert(HTable,cmd);
        if( c == 'd')
            deleteFromHTable(HTable, cmd);
        if( c == 'l')
            listHashTable(HTable, fout);
        if( c == 'f')
        {
            int var = find(HTable,cmd);
            if(var == 0)
            {
                fprintf(fout,"\n Not found \n");
            }
            else
            {
                fprintf(fout,"\n It was found at position %d \n",var);
            }
        }
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
