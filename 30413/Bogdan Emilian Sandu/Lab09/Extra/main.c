#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    struct node *next;
}stackN;

typedef struct stack{
    int nr;
    stackN *top;
    stackN *bottom;
}stackH;

stackN *createN(int key){
    stackN *p;
    p = (stackN*)malloc(sizeof(stackN));
    if(p == NULL) exit(1);
    p->key = key;
    p->next = NULL;
    return p;
}
stackH *createS(){
    stackH *p;
    p = (stackH*)malloc(sizeof(stackH));
    if(p == NULL) exit(1);
    p->nr = 0;
    p->bottom = NULL;
    p->top = NULL;
    return p;
}

void push(stackH *stack,stackN *p){
    if(stack->nr == 0) {
        stack->top = stack->bottom = p;
        p->next = NULL;
        stack->nr++;
    }
    else {
        p->next = stack->top;
        stack->top = p;
        stack->nr++;
    }
}
stackN *pop(stackH *stack){
    stackN *p;
    if(stack->nr == 0) return NULL;//empty
    if(stack->nr == 1){
        p = stack->top;
        stack->top = stack->bottom = NULL;
        stack->nr--;
    }
    else {
        p = stack->top;
        stack->top = stack->top->next;
        stack->nr--;
    }
    return p;
}

void printS(stackH *stack,char c, char *file){
    FILE *output;
    output = fopen(file,"a");
    stackN *p;
    fprintf(output,"%c: ",c);
    if(stack->nr == 0) {
        fprintf(output,"\n");
        fclose(output);
        return;
    }
    p = stack->top;
    while(p != NULL){
        fprintf(output,"%d ",p->key);
        p = p->next;
    }
    fprintf(output,"\n");
    fclose(output);
}
void moveDisc(stackH *A, stackH *B){
    stackN *p;
    p = pop(A);
    push(B,p);
}
void TowersOfHanoi(int nr,stackH *A, stackH *B, stackH *C,char a, char b, char c,char *file){
    if(nr > 0){
        TowersOfHanoi(nr-1,A,C,B,a,c,b,file);//A,C,B; A B
        moveDisc(A,C);
        printS(A,a,file);
        printS(B,b,file);
        printS(C,c,file);
        FILE *output = fopen(file,"a");
        fprintf(output,"---\n");
        fclose(output);
        TowersOfHanoi(nr-1,B,A,C,b,a,c,file);
    }
}

int main(int argc, char *argv[]) {
    int nr;
    char a = 'A',b = 'B', c = 'C';
    FILE *input,*output;
    input = fopen(argv[1],"r");
    output = fopen(argv[2],"w");
    fclose(output);
    if(input == NULL)
        exit(1);
    fscanf(input,"%d",&nr);
    fclose(input);
    stackH *A,*B,*C;
    A = createS();
    B = createS();
    C = createS();
    for(int i = nr; i >= 1; i--){
        stackN *p;
        p = createN(i);
        push(A,p);
    }
    printS(A,a,argv[2]);
    printS(B,b,argv[2]);
    printS(C,c,argv[2]);
    output = fopen(argv[2],"a");
    fprintf(output,"---\n");
    fclose(output);
    TowersOfHanoi(nr,A,B,C,a,b,c,argv[2]);
    return 0;
}
