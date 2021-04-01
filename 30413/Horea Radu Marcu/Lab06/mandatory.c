#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B 7
int f (char *key)
{
    int sum, len;
    sum = 0;
    len = strlen(key);
    int i;
    for(i = 0; i < len; i++)
        sum += key[i];
    return (sum % B);
}
typedef struct cell
{
    char key[60];
    struct cell *next;
} NodeT;
NodeT *BucketTable[B];
int find(char *key)
{
    int x = f(key);
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    p = BucketTable[x];
    while(p != NULL)
    {
        if(strcmp(key, p->key) == 0) return 1;
        p = p->next;
    }
    return 0;
}
int deleteNode(char *key)
{
    int x = f(key);
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    NodeT *q = (NodeT*)malloc(sizeof(NodeT));
    p = BucketTable[x];
    if(p == NULL) return 0;
    q = p;
    if(p->next == NULL && strcmp(p->key, key) == 0) BucketTable[x] = 0;
    else
    {
        if(strcmp(p->key, key) == 0) BucketTable[x] = p->next;
        int ok = 1;
        while(ok == 1)
        {
            if(strcmp(p->key, key) == 0)
            {
                q->next = p->next;
                ok = 0;
            }
            else
            {
                q = p;
                p = p->next;
                if(p == NULL) ok = 0;
            }
        }
    }
    free(p);
    return 1;
}
int main(int argc,char * argv[])
{
    FILE * fin = fopen(argv[1], "r");
    FILE * fout = fopen(argv[2], "w");
    char *cuv = (char*)malloc(32*sizeof(char));
    NodeT *p;
    while(fscanf(fin, "%s", cuv) == 1)
    {
        if(cuv[0] == 'i')
        {
            //insert
            char *aux = (char*)malloc(32*sizeof(char));
            strcpy(aux, cuv + 1);
            p = (NodeT*)malloc(sizeof(NodeT));
            if(p)
            {
                strcpy(p->key, aux);
                p->next == NULL;
                int h;
                h = f(p->key);
                if(BucketTable[h] == NULL)
                {
                    BucketTable[h] = p;
                    p->next == NULL;
                }
                else
                {
                NodeT *q = (NodeT*)malloc(sizeof(NodeT));
                q = BucketTable[h];
                while(q->next != NULL) q = q->next;
                q->next = p;
                }
            }
        }
        if(cuv[0] == 'f')
        {
            //find
            char *aux = (char*)malloc(32*sizeof(char));
            strcpy(aux, cuv + 1);
            int ok = find(aux);
            if(ok == 1)
            {
                fprintf(fout, "Yes, found value %s with Table Index: %d.\n",aux, f(aux));
            }
            else fprintf(fout, "No, value %s not found in the table.\n", aux);
        }
        if(cuv[0] == 'd')
        {
            //delete
            char *aux = (char*)malloc(32*sizeof(char));
            strcpy(aux, cuv + 1);
            deleteNode(aux);
        }
        if(cuv[0] == 'l')
        {
            //list
            int i=0;
            for(i=0;i<B;i++)
            {
                NodeT *q = BucketTable[i];
                if (q != NULL)
                {
                    fprintf(fout, "Table contents for value %d: ", i);
                    while(q != NULL)
                    {
                        fprintf(fout, "%s ", q->key);
                        q = q->next;
                    }
                }
                else fprintf(fout, "No table contents for value %d.", i);
                fprintf(fout,"\n");
            }
        }
    }
    return 0;
}
