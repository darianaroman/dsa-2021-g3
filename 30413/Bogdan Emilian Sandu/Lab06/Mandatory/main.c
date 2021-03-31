#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define B 26

typedef struct node
{
    char name[50];
    struct node *next;
} NodeL;
int hashf(char *s)
{
    int sum = 0;
    for(int i = 0; i < strlen(s); i++)
        sum += s[i];
    return (sum % B);
}
bool find(NodeL *BucketTable[], char *name,FILE *out)
{
    NodeL *p;
    int hval;
    hval = hashf(name);
    p=BucketTable[hval];
    while(p != NULL)
    {
        if(strcmp(p->name,name) == 0)
        {
            fprintf(out,"Found %s\n",name);
            return true;
        }
        p=p->next;
    }
    fprintf(out,"Not found\n");
    return false;
}
void insertN(NodeL *BucketTable[],char *name,FILE *out)
{
    NodeL *p;
    int h;
    p = (NodeL*)malloc(sizeof(NodeL));
    if(p != NULL)
    {
        strcpy(p->name,name);
        h=hashf(name);
        if(BucketTable[h] == NULL)
        {
            BucketTable[h] = p;
            p->next = NULL;
        }
        else if(find(BucketTable,name,out)==false)
        {
            p->next = BucketTable[h];
            BucketTable[h] = p;
        }
        else fprintf(out,"Already exists");
    }
    else exit(1);
}
void listHash(NodeL *BucketTable[],FILE *out)
{
    NodeL *p;
    for( int i = 0; i < B ; i++)
    {
        if(BucketTable[i] != NULL)
        {
            fprintf(out,"Bucket for has value %d\n",i);
            p=BucketTable[i];
            while(p != NULL)
            {
                fprintf(out,"%s ",p->name);
                p = p->next;
            }
            fprintf(out,"\n");
        }
    }
    fprintf(out,"\n---\n");
}
void deleteHash(NodeL *BucketTable[],char *name,FILE *out)
{
    NodeL *p1,*p;
    int hval;
    hval = hashf(name);
    if(BucketTable[hval] != NULL)
    {
        p = BucketTable[hval];
        p1 = NULL;
        while(p != NULL)
        {
            if(strcmp(p->name,name) == 0) break;
            p1 = p;
            p = p->next;
        }
        if(p == BucketTable[hval])
        {
            p1 = p;
            p = p->next;
            BucketTable[hval]=p;
            free(p1);
        }
        else if(p->next == NULL)
        {
            p1->next=NULL;
            free(p);
        }
        else
        {
            p1->next = p->next;
            free(p);
        }
    }
    else fprintf(out,"Value not in table\n");
}
int main(int argc, char *argv[])
{
    FILE *in,*out;
    in=fopen(argv[1],"r");
    out=fopen(argv[2],"w");
    fclose(out);
    NodeL *BucketTable[B];
    for (int i = 0; i < B; i++)
        BucketTable[i]=NULL;
    char s[50];
    while(fscanf(in,"%s",s) == 1)
    {
        switch(s[0])
        {
        case 'i':
            strcpy(s,s+1);
            out=fopen(argv[2],"a");
            insertN(BucketTable,s,out);
            fclose(out);
            break;
        case 'd':
            strcpy(s,s+1);
            out=fopen(argv[2],"a");
            deleteHash(BucketTable,s,out);
            fclose(out);
            break;
        case 'l':
            out=fopen(argv[2],"a");
            listHash(BucketTable,out);
            fclose(out);
            break;
        case 'f':
            strcpy(s,s+1);
            out=fopen(argv[2],"a");
            find(BucketTable,s,out);
            fclose(out);
            break;
        default:
            printf("Error");
            exit(2);
        }
    }
    return 0;
}
