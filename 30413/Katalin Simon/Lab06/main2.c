#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///alp prob7
//slots are going to be the initial of the last names (in case of romanian names and Last name-first name order)
///slots will hold a pointer to a SLL
//DEFINE SLL FOR COLLISION RESOLUTION
//----- Listing.6.1 --- Code part 01 ----------------------
// A simple hash function.}
#define B 26 // 26 letters in the alphabet, the size of the bucket table

FILE *fin;
FILE *fout;

int f(char *key)
{
    int i=(int) (key[1]);
    return i;
  ///generating ascii code of key[1] in comparison with ascii code of A
}

typedef struct cell
{
  char key[60];
  struct cell *next;
} NodeT;

NodeT *BucketTable[B];
//NodeT *BucketTable[]--

//we could work with ascii codes? letter - code of A(capital<-with the condition that names are provided in this format: Doe Jane-first letter capitalized)
// Initializind the table to empty.}
 void initializeSlots(NodeT *BucketTable[])
{
    for (int i = 0; i < B; i++)
        BucketTable[i]= NULL;
}
//----- Listing.6.4 --- Code part 04 ----------------------
// Looking for a string key in a hash table.}
NodeT *findCell(NodeT *BucketTable[], char* key)
{
    NodeT *p;
    int h=f(key);
    p = BucketTable[ h ];// IN CASE WE FOUND THE HASH AND STORED IT IN h=int(ptr->key[1])-int(A)
    while (p != NULL)
    {
      if (strcmp(key, p->key) == 0)//??
        return p;
      p = p->next;
    }
    return NULL; // not found
}//message generated outside function

int deleteByKey(NodeT *BucketTable[], char* givenKey)
{
	int h=f(givenKey);
	int i=0;
	while(i<=B && i!=h)
    {
        i++;
    }
    if(i!=h)
    {
        fprintf(output, "Problem deleting person named %s, since he/she was nat inserted bebore\n", givenKey)
    }
    else
    {
        NodeT *q, *q1;
        q1 = NULL; /* initialize */
        q = BucketTable[ h ];
        q=findCell(BucketTable[],givenkey);
        if ( q != NULL )
        {   /* found a node with supplied key */
            q1 = q;
            if ( q == BucketTable[h] )
              { /* is the first node */
                BucketTable[h] = BucketTable[h]->next;
                free( q ); /* release memory */
              }
              else
              { /* other than first node */
                q1->next = q->next;
                free( q ); /* release memory */
              }
              return 1; // success
            }
            return 0; // failure
            }
}

// Steps in inserting a new record in a hash table.}

// Listing the contents of a hash table.}
void shownode(NodeT *p)
{
    printf("%s\n", p->key);
}

void listTable(NodeT *BucketTable[])
{
    int i;
    for (i = 0; i < B; i++)
  if (BucketTable[ i ] != NULL)
  {
    printf("Bucket for hash value %d\n", i);
    p =BucketTable[ i ];
    while (p != NULL)
    {
      showNode(p);
      p = p->next;
    }
  }
}

int main(int argc, char *argv[])
{
    if(argc==1)
    {
        printf("Please provide the command line arguments");
        return 0;
    }

    fin=fopen(argv[1], "r");
    fout=fopen(argv[2], "w");
    char names[100];//assume words won't be longer than 100 characters
    fscanf(fin, "%s", words);

    while (fscanf(fin,"%s",names) != EOF && strcmp(names, "*") != 0)
    {
        fprintf(fout, "Press *+Enter to exit./Provide * to exit" );
        //printf("%s",c);
        //process info
        switch(names[0])
        {
            case 'i':
                //insert
                instertName(BucketTable[],names);
                break;

            case 'd':
                //delete
                if(!deleteByKey(BucketTable[],key))
                {
                    fprintf(output, "Problem deleting person named %s, since he/she was nat inserted bebore\n", names);
                }
                break;

            case 'f':
                //find but use strcasecmp to avoid confusion
                NodeT *p;
                p=findCell(BucketTable[],names);
                if(!p)
                {
                    fprintf(output, "no");
                }
                else
                {
                    fprintf(output, "yes");
                }
                break;

            case 'l':
                //listing
                listTable(BucketTable[]);
                break;
            default:
                fprintf(output, "Error! input is not correct");
        }
    }

   fclose(fin);
   fclose(fout);
    return 0;
}
///error: expected declaration or statement at end of input
