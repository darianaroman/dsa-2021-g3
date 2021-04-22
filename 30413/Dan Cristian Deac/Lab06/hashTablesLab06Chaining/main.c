#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Hash 666013
#define B 1013


int f(char *key) /// this computes the hash of a string
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


NodeT *find(NodeT **BucketTable, char *key, int index)
{
    NodeT *p = BucketTable[ f(key) ];
    while (p != NULL)
    {
        if (strcmp(key, p->key) == 0)
            return p;
        index++;
        p = p->next;
    }
    return NULL;
}
int count,count2;
void insertNode(NodeT **BucketTable, char *key)
{

    NodeT *p = (NodeT *) malloc(sizeof(NodeT));
    if (p)
    {

        strcpy(p->key, key);
        p->next = NULL;

        int h = f(p->key);

        if (BucketTable[ h ] != NULL)
        {

            NodeT *q = BucketTable[ h ];

            while(q->next != NULL)
            {
                 q = q->next;
            }

            q->next = p;
           //q = p;

        }
        else
        {
           BucketTable[ h ] = p;
        }
    }
    else
        printf("error allocating memory");
}


void listContents (NodeT **BucketTable, char *argv)
{
    FILE *g = fopen(argv, "a");

    for (int i = 0; i < B; i++)
      if (BucketTable[ i ] != NULL)
      {
        fprintf(g,"Bucket for hash value %d\n", i);
        NodeT *p = BucketTable[ i ];
        while (p != NULL)
        {
            //showNode(p);
            fprintf(g,"%s\n", p->key);
            p = p->next;
        }
      }
}
void listContentss (NodeT **BucketTable)
{


    for (int i = 0; i < B; i++)
      if (BucketTable[ i ] != NULL)
      {
        printf("Bucket for hash value %d\n", i);
        NodeT *p = BucketTable[ i ];
        while (p != NULL)
        {
            //showNode(p);
            printf("%s\n", p->key);
            p = p->next;
        }
      }
}
void deleteEl(NodeT **BucketTable, char *key)
{
    NodeT *p = find(BucketTable, key,0);
    if (p!=NULL)
    {
        strcpy(p->key , p->next->key);
        p->next = p->next->next;

        //printf("deleted");
    }
    else printf( "element does not exist ");
}

int main()//int argc, char *argv[])
{

    NodeT *BucketTable[B];

    for (int i = 0; i < B; i++)
        BucketTable[i] = NULL;



    insertNode(BucketTable, "Jenna Toils");
    insertNode(BucketTable, "Toils Jenna");
    insertNode(BucketTable, "Toil sJenna");
    insertNode(BucketTable, "Magay Ghey");
    insertNode(BucketTable, "Mike Hawk");
    insertNode(BucketTable, "Hugh Jass");
    int index =0;
    if(find(BucketTable, "Mike Hawk", index)!=NULL)
    printf("yes %d\n", index );

    deleteEl(BucketTable, "Jenna Toils");

    listContentss(BucketTable);


    return 0;
}
