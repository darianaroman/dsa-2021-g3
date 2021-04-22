#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 25

typedef struct node
{
    char key[40];
    struct node* next;
} NodeT;

NodeT* createnode(char *data)
{
    NodeT *p;
    p=(NodeT* )malloc(sizeof(NodeT));
    if(p)
    {
        strcpy( p->key,data );
        p->next= NULL;
    }
    return p;
}

int Gamma(char *key)
{
    int sum,len;
    sum= 0;
    len= strlen(key);
    for(int i=0; i<len; i++)
        sum+= key[i];
    return (sum%B);
}

void insert(NodeT* HTable[B], char* data)
{
    NodeT* p;
    p= createnode(data);
    int h= Gamma(data);
    p->next= HTable[h];
    HTable[h]= p;
}

void list(NodeT* HTable[B], FILE *fout)
{
    NodeT *p = NULL;
    int i;
    for( i=0;i<B; i++ )
    {
        p = HTable[i];
        fprintf(fout, "%d: ", i);
        while( p!=NULL )
        {
            fprintf(fout, "%s,", p->key);
            p= p->next;
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
}

int find(NodeT* HTable[B], char* val)
{
    int h=Gamma(val);
    NodeT* p;
    p=HTable[h];
    while( p!=NULL )
    {
        if( strcmp(p->key, val) == 0 )
            return h;
        p= p->next;
    }
    return 0;
}

void deleteHTable(NodeT *HTable[B], char *val)
{
    int h= Gamma(val);
    NodeT *p= NULL;
    p= HTable[h];
    NodeT *temp= NULL;
    if( strcmp(p->key, val) == 0 )
    {
        HTable[h] = p->next;
        free(p);
    }
    else
    {
        while( p != NULL )
        {
            if(strcmp(p->key, val) == 0)
            {
                temp->next = p->next;
                free(p);
            }
            temp = p;
            p = p->next;
        }
    }
}

int main(int argc, char* argv[])
{
    FILE *fin,*fout;
    fin=fopen(argv[1],"r");
    fout=fopen(argv[2],"w");
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
    NodeT* HTable[B];
    for ( i=0; i<B; i++ )
        HTable[i] = NULL;

    char cmd[10];
    char c;
    while( fscanf(fin,"%s", cmd) != EOF)
    {
        c=cmd[0];
        strcpy(cmd,cmd+1);
        switch(c)
        {
            case 'i': insert(HTable,cmd); break;
            case 'd': deleteHTable(HTable, cmd); break;
            case 'f': {int pos= find(HTable,cmd);
                      if(pos == 0) fprintf( fout, "\n Not found \n" );
                        else fprintf( fout, "\n Found at position %d \n\n", pos );
                        break;
            }
            case 'l': list(HTable, fout); break;
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}
