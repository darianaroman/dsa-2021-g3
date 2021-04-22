#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 30

typedef struct node
{
    char name[30];
    struct node *next;
} person;

person *BucketTable[TABLE_SIZE];

int hash(char *name)
{
    int sum = 0, i;
    for(i=0; i<strlen(name); i++)
        sum = sum + name[i];
    return (sum % TABLE_SIZE);
}

void initHashTable()
{
    int i;
    for(i=0; i<TABLE_SIZE; i++)
        BucketTable[i] = NULL;
}

void printTable(FILE *file)
{
    int i;
    for(i=0; i<TABLE_SIZE; i++)
        if(BucketTable[i] == NULL)
            fprintf(file,"\n%d ---- ",i);
        else
        {
            fprintf(file,"\n%i",i);
            person *tmp = BucketTable[i];
            while(tmp != NULL)
            {
                if(tmp->next == NULL)
                    fprintf(file," %s",tmp->name);
                else
                    fprintf(file," %s -",tmp ->name);
                tmp = tmp->next;
            }
        }
}

int insert(person *p)
{
    if(p == NULL)
        return 0;
    int index = hash(p->name);
    p->next = BucketTable[index];
    BucketTable[index] = p;
    return 1;
}

person *find(char *name)
{
    int index = hash(name);
    person *tmp = BucketTable[index];
    while(tmp != NULL && stricmp(tmp->name,name) != 0)
        tmp = tmp->next;
    return tmp;
}

person *delete(char *name)
{
    int index = hash(name);
    person *tmp = BucketTable[index];
    person *prev = NULL;
    while(tmp != NULL && stricmp(tmp->name,name) != 0)
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp == NULL)
        return NULL;
    if(prev == NULL)
        BucketTable[index] = tmp->next;
    else
        prev->next = tmp->next;
    return tmp;
}

int main(int *argc, char *argv[])
{
    char name[30];
    FILE *f = fopen(argv[1],"r");
    FILE *g = fopen(argv[2],"w");

    initHashTable();
    if(f == NULL)
    {
        printf("File not found");
        exit(1);
    }
    while(fgets(name, sizeof(name), f))
    {
        switch(name[0])
        {
            case 'i':
                insert(name+1);
                break;

            case 'd':
                delete(name+1);
                break;

            case 'f':
                if(find(name+1)!=NULL)
                    fprintf(g,"Person %s was found", find(name+1)->name);
                else
                    fprintf(g,"Person %s was not found",find(name+1)->name);
                break;

            case 'l':
                printTable(g);
                break;

            default:
                printf(g,"The only available functions are: i,d,f,l\n");
        }
    }
    printf("The program ran successfully. Please check %s", argv[2]);
    return 0;
}
