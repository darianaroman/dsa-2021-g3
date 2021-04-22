#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
///bucket table
typedef struct cell{
  char key[60];
  struct cell *next;
} NodeT;
///Initializind the table to empty
void empty(NodeT *node[]){
    for (int i = 0; i < N; i++)
        node[i] = NULL;
}
///creating the hash table
int hash(char *key){
    int sum,length,i;
    sum = 0;
    length = strlen(key);
    for (i = 0; i < length; i++)
        sum += key[i];
    return (sum % N);
}
///find a name in the table
NodeT *find(char *key,NodeT *BucketTable[]){
    int hashValue = hash(key);
    NodeT *p;
    //p = (NodeT*)malloc(sizeof(NodeT));
    p = BucketTable[hashValue];
    while (p != NULL){
        if (strcmp(key,p->key) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
///insert a name
void insert(char *key,NodeT *BucketTable[],char *fileName){
    NodeT *p,*found;
    int h;
    FILE *out = fopen(fileName,"a");
    p = (NodeT*)malloc(sizeof(NodeT));
    if (p){
        strcpy(p->key,key);
        //p->next = NULL;
        h = hash(key);
        if (BucketTable[h] == NULL){
            BucketTable[h] = p;
            p->next = NULL;
        }
        else{
            found = find(key,BucketTable);
            if (found != NULL){
                fprintf(out,"Already exists\n");
                fclose(out);
                return;
            }
            else{
                p->next = BucketTable[h];
                BucketTable[h] = p;
            }
        }
    }
    else{
        fprintf(out,"ERROR!\n");
        fclose(out);
        exit(1);
    }
    fclose(out);
}

///delete a node
void deleting(char *key,NodeT **BucketTable){
    NodeT *currentNode,*prev;
    int h;
    h = hash(key);
    currentNode = BucketTable[h];
    prev = NULL;
    while(currentNode != NULL){
        if (strcmp(key,currentNode->key) == 0){
            break;
        }
        prev = currentNode;
        currentNode = currentNode->next;
    }
    if (currentNode == BucketTable[h]){
        prev = currentNode;
        currentNode = currentNode->next;
        BucketTable[h] = currentNode;
        free(prev);
    }
    else if (currentNode->next == NULL){
        prev->next = NULL;
        free(currentNode);
    }
    else{
        prev->next = currentNode->next;
        free(currentNode);
    }
}
///listing
void list(NodeT **BucketTable,char *fileName){
    NodeT *p;
    FILE *out = fopen(fileName,"a");
    for(int i = 0;i < N;i++){
        if (BucketTable[i] != NULL){
            fprintf(out,"Bucket for hash value %d\n",i);
            p = BucketTable[i];
            while (p != NULL){
                fprintf(out,"%s ",p->key);
                p = p->next;
            }
            fprintf(out,"\n");
        }
    }
    fclose(out);
}
int main() {
    FILE *in = fopen("in.txt","r");
    FILE *out = fopen("out.txt","w");
    if (in == NULL){
        printf("CAN'T OPEN FILE");
        exit(1);
    }
    if (out == NULL){
        printf("CAN'T OPEN FILE");
        exit(1);
    }
    fclose(out);
    NodeT **BucketTable;
    BucketTable = (NodeT**)malloc(N*sizeof(NodeT*));
    empty(BucketTable);
    NodeT *found;
    char key[61],name[60];
    while(fscanf(in,"%s",key) == 1){
        strcpy(name,key+1);
        switch(key[0]){
            case 'i':
                insert(name,BucketTable,"out.txt");
                break;
            case 'd':
                deleting(name,BucketTable);
                break;
            case 'f':
                found = find(name,BucketTable);
                if (found != NULL){
                    out = fopen("out.txt","a");
                    fprintf(out,"YES!\n");
                    fclose(out);
                }
                else{
                    out = fopen("out.txt","a");
                    fprintf(out,"NO!\n");
                    fclose(out);
                }
                break;
            case 'l':
                list(BucketTable,"out.txt");
                break;
            default:
                out = fopen("out.txt","a");
                fprintf(out,"INVALID OPERATION!\n");
                fclose(out);
        }
    }
    fclose(in);
    return 0;
}
