#include <stdio.h>
#include <stdlib.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode){
    FILE *pf = fopen(path,mode);
    if (pf == NULL){
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
typedef struct StackNode {
    int size;
    struct StackNode* next;
}NodeS;
NodeS* newNode(int size){
    NodeS* stackNode = (NodeS*)malloc(sizeof(NodeS));
    stackNode->size = size;
    stackNode->next = NULL;
    return stackNode;
}
int isEmpty(NodeS* root){
    return !root;
}
void push(NodeS** root, int size){
    NodeS* stackNode = newNode(size);
    stackNode->next = *root;
    *root = stackNode;
}
int pop(NodeS** root){
    if (isEmpty(*root))
        return -1;
    NodeS* temp = *root;
    *root = (*root)->next;
    int popped = temp->size;
    return popped;
}
int peek(NodeS* root){
    if (isEmpty(root))
        return -1;
    return root->size;
}
void printPeg (char ch, NodeS* root, FILE *pOut){
    fprintf(pOut, "\n%c : ", ch);
    while(!isEmpty(root)){
        fprintf(pOut, "%d ", peek(root));
        pop(&root);
    }
}
void printInOrder (NodeS** A, NodeS** B, NodeS** C, char a, char b, char c, FILE *pOut)
{
    fprintf(pOut,"\n");
    if (a < b && a < c){
        printPeg(a,*A,pOut);
        if (b < c){
            printPeg(b,*B,pOut);
            printPeg(c,*C,pOut);
        }
        else{
             printPeg(c,*C,pOut);
             printPeg(b,*B,pOut);
        }
    }
    else if (b < a && b < c){
        printPeg(b,*B,pOut);
        if (a < c){
            printPeg(a,*A,pOut);
            printPeg(c,*C,pOut);
        }
        else{
             printPeg(c,*C,pOut);
             printPeg(a,*A,pOut);
        }
    }
    else {
        printPeg(c,*C,pOut);
        if (a < b){
            printPeg(a,*A,pOut);
            printPeg(b,*B,pOut);
        }
        else{
             printPeg(b,*B,pOut);
            printPeg(a,*A,pOut);
        }
    }
}
void Hanoi (NodeS** A, NodeS** B, NodeS** C, char a, char b, char c, int n, FILE *pOut){

    if (n == 1){
        push(B, pop(A));       /// move the last disk from A to B
        printInOrder(A,B,C,a,b,c,pOut);
        return;
    }
    Hanoi(A,C,B,a,c,b,n-1,pOut);    /// move n-1 disks from A to C(=auxiliary peg)
    push(B, pop(A));           /// move the last disk from A to B
    printInOrder(A,B,C,a,b,c,pOut);
    Hanoi(C,B,A,c,b,a,n-1,pOut);    /// move n-1 disks C(=auxiliary peg) to B
}
int main(int argc, char *argv[]){
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    int n;
    fscanf(pIn,"%d",&n);
    NodeS *A = NULL, *B = NULL, *C = NULL;
    for (int i = n; i >= 1; i--)
        push(&A,i);
    printInOrder(&A,&B,&C,'A','B','C',pOut);
    Hanoi(&A,&B,&C,'A','B','C',n,pOut); /// move from A to B
    fclose(pIn);
    fclose(pOut);
    return 0;
}
