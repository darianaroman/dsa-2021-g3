#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 30

int f(char *key){
  int i, sum;
  sum = 0;
  for (i = 0; i < strlen(key); i++)
    sum += key[i];
  return(sum % N);
}

typedef struct cell{
  char key[60];
  struct cell *next;
} NodeT;

NodeT* find(NodeT *BucketTable[N], char key[]){
    NodeT *p = BucketTable[N];
    while (p != NULL){
        if (strcmp(key, p->key) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

NodeT* createNode(char *data){
    NodeT *p;
    p=(NodeT*)malloc(sizeof(NodeT));
    if(p){
        strcpy(p->key, data);
        p->next= NULL;
        }
    return p;
}

void insert(NodeT* BucketTable[N], char* data){
    NodeT* p;
    p=createNode(data);
    int hash=f(data);
    p->next=BucketTable[hash];
    BucketTable[hash]=p;
}

void deleteFromHTable(NodeT *HTable[N], char *data){
    int hash = f(data);
    NodeT *p = NULL;
    p = HTable[hash];
    NodeT *aux = NULL;
    if(strcmp(p->key, data) == 0){
        HTable[hash] = p->next;
        free(p);
        }
    else{
        while(p != NULL){
            if(strcmp(p->key, data) == 0){
                aux->next = p->next;
                free(p);
            }
            aux = p;
            p = p->next;
        }
    }
}


void list(NodeT *BucketTable[N], FILE *out){
    NodeT *p=NULL;
    for (int i=0;i<N; i++)
    if (BucketTable[i] != NULL){
        fprintf(out, "Bucket for hash value %d\n", i);
        p=BucketTable[i];
        while (p != NULL){
            fprintf(out, "%s ",  p->key);
            p = p->next;
            }
        fprintf(out, "\n");
        }
}


int main(int argc, char *arcv[])
{
    //FILE *in=fopen("./input", "r");
    //FILE *out=fopen("./output", "w");
    FILE *in=fopen(arcv[1], "r");
    FILE *out=fopen(arcv[2], "w");


    char command, key[50];
    NodeT *BucketTable[N];
    for (int i = 0; i < N; i++)
        BucketTable[i] = NULL;

     do {
        char *word=(char *)malloc(3*sizeof(char));
        fscanf(in, "%s ", word);
        command=word[0];
        strcpy(key,word+1);

        if (command=='i')
            insert(BucketTable, key);
        else if(command=='d')
            deleteFromHTable(BucketTable, key);
        else if(command=='f'){
            if (find(BucketTable, key)!=NULL)
                fprintf(out, "node %s is in list\n", key);
            else
                fprintf(out, "node %s not found\n", key);
            }
        else if (command=='l'){
            list(BucketTable, out);
        fprintf(out, "\n");
        }
        else
            fprintf(out, "\ncommand %c is not valid\n", command);

        free(word);
    } while (!feof(in));



    return 0;
}
