#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 50
int hashFunction(char *key)
{
    int i, sum;
    sum = 0;
    for (i = 0; i < strlen(key); i++)
        sum += key[ i ];

    return(sum % B);
}

typedef struct cell
{
    char key[60];
    /* other useful info */
    struct cell *next;
} NodeT;

NodeT *BucketTable[B];

NodeT* initalization()
{
    if(BucketTable)
    {
        for (int i = 0; i < B; i++)
            BucketTable[i] = NULL;
    }
    return BucketTable[B];

}
int *find(NodeT *BucketTable[B],char *key)
{
    NodeT *p;
    int h;
    h=hashFunction(key);
    p = BucketTable[ h ];
    while (p != NULL)
    {
        if (strcmp(key, p->key) == 0)
            return h;
        p = p->next;
    }
    return 0; /* not found */
}

void insertNewRec(NodeT *BucketTable[B], char *key)
{
    int h;
    NodeT * p = (NodeT *) malloc(sizeof(NodeT));
    if (p)
    {
        strcpy(p->key,key);
        p->next = NULL;
        h = hashFunction(p->key);

        if (BucketTable[ h ] == NULL)
        {
            // empty slot
            BucketTable[ h ] = p;
            p->next = NULL;
        }
    }
    else
    {
        int *q;
        q = find(BucketTable,p->key);
        if (q == 0)
        {
            p -> next = BucketTable[ h ];
            BucketTable[ h ] = p;

        }



    }


}
void deleteElement(NodeT *BucketTable[B], char *givenkey)
{
    NodeT *p;

    if(find(BucketTable,givenkey)==0)
        return;
    else
    {
        int h;
        h=hashFunction(givenkey);
        if(BucketTable[h]->next==NULL)
        {
            BucketTable[h]=NULL;
        }

        else
        {
            p=BucketTable[h];
            NodeT *q,*t;
            t=NULL;
            q=p;

            while(q!=NULL)
            {
                if(strcmp(q->key,givenkey)==0)
                    break;
                t=q;
                q=q->next;
            }
            if(q==p)
            {
                q->next=p;
                free(q);
            }
            else if(q->next==NULL)
            {
                t->next=NULL;
                free(q);
            }
            else
            {
                t->next=t->next->next;
                free(q);
            }
        }
    }
}

void print(NodeT *BucketTable[B],FILE *f)
{

    NodeT *p;
    p = (NodeT *) malloc(sizeof(NodeT));


    for (int i = 0; i < B; i++)
        if (BucketTable[ i ] != NULL)
        {
            fprintf(f,"\nBucket for hash value %d: ", i);
            NodeT *p;
            p = (NodeT *) malloc(sizeof(NodeT));

            p =BucketTable[ i ];
            while (p != NULL)
            {
                fprintf(f,"%s\n",p->key);
                p = p->next;
            }
        }


}
int main(int argc, char **argv)
{
    BucketTable[B]=initalization();

    FILE *fin=fopen(argv[1],"r");
    FILE *fout=fopen(argv[2],"w");

    int lines=0;
    char b;
    b=fgetc(fin);
    while(b!=EOF)
    {
        if(b=='\n')
            lines++;
        b=fgetc(fin);
    }
    rewind(fin);
    //printf("%d\n",lines);
    int j;
    char name[30],command;
    for(j=0; j<lines-1; j++)
    {
        fgets(name,30,fin);
        name[strlen(name)-1]=NULL;

        switch(name[0])
        {
        case 'i':
            insertNewRec(BucketTable,name+1);
            break;

        case 'f':
            if(find(BucketTable,name+1)!=0)
                fprintf(fout,"\n%s found at table index %d\n",name+1,find(BucketTable,name+1));

            else
                fprintf(fout,"\n%s not found!\n",name+1);

            break;

        case 'l':
            print(BucketTable,fout);
            break;

        case 'd':
            deleteElement(BucketTable,name+1);
            break;

        default: fprintf(fout,"\nCommand Unknown for %s\n",name+1);
            break;






        }
    }

    return 0;
}
