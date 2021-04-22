#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 20

int f(char *key)
{
    int i, sum;
    sum = 0;
    for (i = 0; i < strlen (key); i++)
        sum += key[ i ];
    return(sum % B);
}

typedef struct cell
{
    char key[60];
    struct cell *next;
} NodeT;


NodeT *createNode(char givenKey[60])
{
    NodeT *p = (NodeT *) malloc (sizeof (NodeT));
    if (p)
    {
        strcpy(p->key , givenKey);
        p->next = NULL;
    }
    return p;
}

NodeT* findWord(int h, char key[60],NodeT *BucketTable[B])
{
    NodeT* p = BucketTable[ h ]; ///here h represents the key in the hash table of the given word
    while (p != NULL)
    {
        if (strcmp(key, p->key) == 0)
            return p;
        p = p->next;
    }
    return NULL; /* not found */
}

void insertWord(NodeT *p, NodeT *BucketTable[B], FILE *ff)
{
    if (p)
    {
        int h = f(p->key);
        if (BucketTable[ h ] == NULL)
        {
            // empty slot
            BucketTable[ h ] = p;
            p->next = NULL;
        }
        else
        {
            NodeT *q = findWord(f(p->key),p->key,BucketTable);
            if (q == NULL)
            {
                /* not found. Insert it */
                p -> next = BucketTable[ h ];
                BucketTable[ h ] = p;
            }
        }
    }
    else
        fprintf(ff, "something went wrong");
}

void printTable(NodeT* BucketTable[B],FILE *ff)
{
    int i;
    for (i = 0; i < B; i++)
        if (BucketTable[ i ] != NULL)
        {
            fprintf(ff, "Bucket for hash value(s) %d\n", i);
            NodeT*p =BucketTable[ i ];
            while (p != NULL)
            {
                fprintf(ff, "%s ",p->key);
                p = p->next;
            }
            fprintf(ff, "\n");
        }
}

void deleteWord(char key[60], NodeT* BucketTable[B], FILE* ff)
{
    if(findWord(f(key),key,BucketTable)!=NULL)
    {
        int h=f(key);
        NodeT *q, *q1;
        q1 = NULL;
        q = BucketTable[h];
        while ( q != NULL )
        {
            if ( strcmp(q->key , key)==0 ) break;
            q1 = q;
            q = q->next;
        }
        if ( q != NULL )
        {
            if ( q == BucketTable[h] )
            {
                if ( BucketTable[h]->next == NULL )
                    BucketTable[h]=NULL;

                else BucketTable[h] = BucketTable[h]->next;

            }
            else
            {

                q1->next = q->next;
                if ( q->next == NULL ) q1->next=NULL;

            }

        }
    }
    else
        fprintf(ff, "The name %s is not in the table\n", key);
}
int main(int argc, char **argv)
{
    FILE *fi=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");

    char name[60],ch,op;
    int i;
    NodeT *BucketTable[B];
    for (i = 0; i < B; i++)
        BucketTable[i] = NULL;
    i=0;
    while(fscanf(fi,"%c",&ch)!=EOF)
    {
        if(ch!='\n')
        {
            name[i]=ch;
            i++;
        }
        else
        {
            op=name[0];
            name[i]=0;
            strcpy(name, name+1);
            NodeT *p,*q;
            p=createNode(name);
            switch (op)
            {
            case 'i':
            {
                insertWord(p, BucketTable, fo);
            }
            break;
            case 'd':
                deleteWord(p->key, BucketTable, fo);
                break;
            case 'l':
                printTable(BucketTable, fo);
                break;
            case 'f':
            {
                q=findWord(f(p->key), p->key, BucketTable);
                if (q==NULL)
                    fprintf(fo, "The name %s is not is the table\n", p->key);
                else fprintf(fo, "The name %s is in the table, at index %d\n", p->key, f(p->key));
            }
            break;
            }
            i=0;
            name[0]=0;
        }
    }
    fclose(fo);
    fclose(fi);

    return 0;
}
