#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct cell
{
    char key[60];
    struct cell *next;
} NodeT;
NodeT *BucketTable[30];
int H(char *key)
{
    char c=key[0];
    if(c>='A'&&c<='Z')
    {
        c=c-'A';
        return (int)c;
    }
    else if(c>='a'&&c<='z')
    {
        c=c-'a';
        return (int)c;
    }
    else
    {
        return -1;
    }
}
int insert(char *key)
{
    int i=H(key);
    if(i!=-1)
    {
        NodeT *p=(NodeT*)malloc(sizeof(NodeT));
        strcpy(p->key,key);
        p->next=NULL;
        if(BucketTable[i]==NULL)
        {
            BucketTable[i]=p;
        }
        else
        {
            p->next=BucketTable[i];
            BucketTable[i]=p;
        }
    }
}
void list()
{
    int i;
    NodeT* p;
    for(i=0; i<=26; i++)
    {
        p=BucketTable[i];
        while(p!=NULL)
        {
            printf("%s \n",p->key);
            p=p->next;
        }
    }
}
void find(char *key)
{
    int c= H(key);
    if(c!=-1)
    {


        int ok=0;
        NodeT* p= BucketTable[c];
        while(p!=NULL&&ok==0)
        {
            if(strcmp(p->key,key)==0)
            {
                ok=1;
            }
        }
        if(ok==0)
        {
            printf("%s not found!", key);
        }
        if(ok==1)
        {
            printf("%s found!", key);
        }
    }
}
int delete(char *key)
{
    int c= H(key);
    if(c!=-1)
    {


        int ok=0, k;
        NodeT* p= BucketTable[c];
        while(p!=NULL&&ok==0)
        {
            if(strcmp(p->key,key)==0)
            {
                ok=1;
            }
        }
        if(ok==1)
        {
            k=0;
            p=BucketTable[c];
            if(strcmp(p->key,key)==0)
            {
                BucketTable[c]=p->next;
                free(p);
            }
            else
            {
                while(k==0)
                {
                    if(strcmp(p->next->key, key)==0)
                    {
                        k=1;
                    }
                }
                p->next=p->next->next;
                free(p);

            }
        }
        if(ok==0)
        {
            printf("%s does not exist!", key);
        }
    }
}
int main()
{
    char c;
    int i;
    char key[60];
    c=getchar();
    while(c!='x')
    {

        if(c=='i')
        {
            i=0;
            c=getchar();
            while(c!='\n')
            {
                key[i++]=c;
                c=getchar();
            }
            key[i]=0;
            insert(key);
        }
        if(c=='l')
        {
            list();
        }
        if(c=='f')
        {
            i=0;
            c=getchar();
            while(c!='\n')
            {
                key[i++]=c;
                c=getchar();
            }
            key[i]=0;
            find(key);
        }
        if(c=='d')
        {
            i=0;
            c=getchar();
            while(c!='\n')
            {
                key[i++]=c;
                c=getchar();
            }
            key[i]=0;
            delete(key);
        }
        c=getchar();
    }
}
