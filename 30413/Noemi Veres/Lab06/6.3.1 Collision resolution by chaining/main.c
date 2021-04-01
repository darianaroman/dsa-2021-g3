#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
/// define cell
typedef struct cell_type
{
    char key[30];
    struct cell_type *next;
} CellT;
CellT *BucketTable[10];
/// hash function
int f(char *key)
{
    /*using the ASCII code of each character, we calculate the sum and then return
    sum%10 - as the idea was to handle collision I didn't write here such a big number*/
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
        sum += key[i];
    return (sum % 10);
}
/// find a given name in the table
CellT *find (char *given)
{
    int pos = f(given);
    CellT *p = BucketTable[pos];
    while (p != NULL)
    {
        if (strcmp(given,p->key) == NULL)
            return p;
        p = p->next;
    }
    return NULL;
}
/// insert a name in a table
void insert (char *given)
{
    CellT *p = (CellT*)malloc(sizeof(CellT)), *q = NULL;
    if (p)
    {
        strcpy(p->key,given);
        p->next = NULL;
        int pos = f(p->key);
        q = BucketTable[pos];
        if (q == NULL)
            BucketTable[pos] = p;
        else
        {
            while (q->next != NULL)
            {
                q = q->next;
            }
            q->next = p;
        }
    }
}
/// delete a name from table
void deleteCell (char *given)
{
    int pos = f(given);
    CellT *p = BucketTable[pos], *p1 = NULL;
    if (p->next == NULL)
        BucketTable[pos] = NULL;
    else
    {
        if (strcmp(p->key,given) == 0)
            BucketTable[pos] = p->next;
        else
        {
            while (p != NULL)
            {
                if (strcmp(p->key,given) == 0) break;
                p1 = p;
                p = p->next;
            }
            p1->next = p->next;
        }
    }
    free(p);
}
/// list the elements
void list(FILE *pOut)
{
    CellT *p = NULL;
    for (int i = 0; i < 10; i++)
        if (BucketTable[i] != NULL)
        {
            fprintf(pOut,"Bucket for hash value %d: ", i);
            p = BucketTable[i];
            while (p != NULL)
            {
                fprintf(pOut,"%s ",p->key);
                p = p->next;
            }
        }
}
int main(int argc, char *argv[])
{
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    for (int i = 0; i < 10; i++)
        BucketTable[i] = NULL;
    char ch, command[31], name[30];
    while(fgets(command,32,pIn) != NULL)
    {
        ch = command[0];
        strcpy(name,command+1);
        switch (ch)
        {
        case 'i':
            insert(name);
            break;
        case 'd':
            deleteCell(name);
            break;
        case 'f':
        {
            CellT *p = find(name);
            if (p!=NULL)
                fprintf(pOut,"yes%d\n",f(name));
            else fputs("no\n",pOut);
            break;
        }
        case 'l':
            list(pOut);
            break;
        default:
            fprintf(pOut,"\nInvalid operation '%c'",ch);
            exit(2);
        }
    }
    fclose(pIn);
    fclose(pOut);
    return 0;
}
