#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hashFunction(char key)
{
    int result = 0;
    result = ((int)(key) - 65 ) % 26; // assuming every given name starts with a capital letter, the names will be given indexes coresponding
    // to their alphabetical order, e.g. a name starting with letter C will be given index 3
    return result;
}

typedef struct cell
{
    char key[50];
    struct cell* next;

} NodeT;

void fillNode(NodeT *q, char name[50])
{
    strcpy(q->key, name);
}

NodeT *findNode(char name[50], NodeT** BucketTable)
{
    NodeT *p;
    int h = hashFunction(name[0]);
    p = BucketTable[h];
    while(p != NULL)
    {
        if(strcmp(name, p->key) == 0)
        {
            return p;
        }
        p = p->next;
    }

    return NULL;
}


void deleteNode(char name[50], NodeT** BucketTable)
{
    NodeT *p;
    p = findNode(name, BucketTable);
    NodeT *q;
    int h = hashFunction(name[0]);
    if(p == BucketTable[h])
    {
        BucketTable[h] = p->next;
    }
    else
    {
        q = BucketTable[h];
        while(q -> next != p)
        {
            q = q->next;
        }
        q -> next = p ->next;
    }
    //then delete
}

int main(char argc, char *argv[])
{
    FILE *fi, *fo;
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "w");
    char command[51];

    ////
    NodeT* BucketTable[26];
    for(int i = 0; i < 26; i++)
    {
        BucketTable[i] = NULL;
    }
    while(fgets(command, 50, fi))
    {
        char *ep = &command[strlen(command)-1];
        while (*ep == '\n' || *ep == '\r')
        {
            *ep-- = '\0';
        }
        if(command[0] == 'i')
        {
            //insert
            NodeT* p;
            p = (NodeT*)malloc(sizeof(NodeT));
            if(p)
            {
                fillNode(p, command+1);
                int h;
                h = hashFunction(p->key[0]);
                if(BucketTable[h] == NULL)
                {
                    BucketTable[h] = p;
                    p->next = NULL;
                }
                else
                {
                    NodeT *q;
                    q = BucketTable[h];
                    while(q->next != NULL)
                    {
                        q = q->next;
                    }
                    q->next = p;
                    p->next = NULL;
                }
            }
            else
            {
                fprintf(fo,"error\n");
                //error
            }

        }
        else if(command[0] == 'd')
        {
            //delete
            deleteNode(command+1, BucketTable);
        }
        else if(command[0] == 'f')
        {
            //find
            NodeT *p;
            p = findNode(command+1, BucketTable);
            if(p != NULL)
            {
                fprintf(fo,"yes, index: %d\n", hashFunction(command[1]));
            }
            else
            {
                fprintf(fo,"no\n");
            }
        }
        else if(command[0] == 'l')
        {
            for(int j = 0; j < 26; j++)
            {
                NodeT *q;
                q = BucketTable[j];
                while(q != NULL)
                {
                    fprintf(fo,"%s\n", q->key);
                    q = q -> next;
                }
            }
        }
    }
    fclose(fi);
    fclose(fo);
    return 0;
}
