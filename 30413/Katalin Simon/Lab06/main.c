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

// Steps in inserting a new record in a hash table.}
void instertName(NodeT *BucketTable[], char* key)
{
    NodeT *p;
    p = (NodeT *) malloc(sizeof(NodeT));
//CHECKING FOR THE NODE IN THE LIST
    if (p)
    {
        fillNode(p);
        int h=f(key);
        h = f(p->key);
        if (BucketTable[ h ] == NULL)
        { // empty slot
             BucketTable[ h ] = p;
              p->next = NULL;
        }
    }
    else
    {
        NodeT *q;
        q = find(p->key);
        int h=f(p->key);
        if (q == 0)
        { /* not found. Insert it */
          p -> next = BucketTable[ h ];
          BucketTable[ h ] = p;
        }
        else
        {/* double key */
          //processRec(p, q);//DOES NOTHING UNTIL DEFINED OTHERWISE
        }
    // suitable message for no memory error IN THIS CASE YES?

}

// Listing the contents of a hash table.}
void shownode(NodeT *p)
{
    printf("%s\n", p->key);
}

void instertName(NodeT *BucketTable[], char* key)
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
int main(int argv, char *argc[])
{
    FILE *fin;
    FILE *fout;
    if(argc==1)
    {
        printf("Please provide the command line arguments");
        return 0;
    }

    fin=fopen(argv[1], "r");
    fout=fopen(argv[2], "w");
    char words[100];//assume words won't be longer than 100 characters
    fscanf(fin, "%s", words);

    while (fscanf(fin,"%s",words) != EOF)
    {
        //
    }
   fclose(fin);
   fclose(fout);
    return 0;
}
///error: expected declaration or statement at end of input
