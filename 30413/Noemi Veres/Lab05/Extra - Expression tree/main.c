#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include <stdbool.h>
typedef struct node_type
{
    char *key;
    struct node_type *left, *right;
}NodeT;
/// create a node
NodeT *createNode(char *givenKey)
{
    NodeT *p = (NodeT*)malloc(sizeof(NodeT));
    strrev(givenKey);
    if (p)
    {
        p->key = givenKey;
        p->left = p->right = NULL; /* leaf node */
    }
    return p;
}
/// stack
typedef struct node_stack {
    NodeT *p;
    struct node_stack* next;
}NodeS;

NodeS* newNode(NodeT *p)
{
    NodeS* stackNode = (NodeS*)malloc(sizeof(NodeS));
    stackNode->p = p;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(NodeS* root)
{
    return !root;
}

void push(NodeS **root, NodeT *p)
{
    NodeS* stackNode = newNode(p);
    stackNode->next = *root;
    *root = stackNode;
    printf("\n%s pushed to stack", p->key);
}

NodeT *pop(NodeS **root)
{
    if (isEmpty(*root)) { puts("\nerror"); return NULL;}
    NodeS* temp = *root;
    *root = (*root)->next;
    NodeT *popped = temp->p;
    free(temp);
    return popped;
}

void peek(NodeS* root)
{
    if (isEmpty(root)) puts("\nNo element in stack");
    printf("\n%s is the top element", root->p->key);
}

void preorder(NodeT *p)
{
  if (p != NULL)
  {
    printf("%s ", p->key);
    preorder(p->left);
    preorder(p->right);
  }
}
int main()
{
    FILE *pIn = fopen("in.txt", "r");
    NodeS* root = NULL;
    char prefix[256] = "", nr[10] = "", symbol[2] = "";
    int ch = fgetc(pIn), i = 0;
    while (ch != '\n')
    {
        prefix[i] = ch;
        i++;
        ch = getc(pIn);
    }
    int l = strlen(prefix);
    prefix[l] = '\0';
    NodeT *p = NULL;
    for (i = l-1; i >= 0; i--)
    {
        if (isdigit(prefix[i]))
        {
            int j = 0;
            while(prefix[i] != ' ')
            {
                nr[j] = prefix[i];
                i--;
                j++;
            }
            nr[j] = '\0';
            p = createNode(nr);
            push(&root,p);
        }
        else
        {
            //puts("\nelse: ");
            //pop(&root);
            //peek(root);
            //pop(&root);
            symbol[0] = prefix[i];
            symbol[1] = '\0';
            //printf("\n%s is symbol\n", symbol);
            //peek(root);
            p = createNode(symbol);
            //printf("%s is symbol\n", symbol);
            //pop(&root);
            //peek(root);
            p->left = pop(&root);
            //peek(root);
            //printf("\n1)%s ",p->left->key);
            p->right = pop(&root);
            //peek(root);
            //printf("\n2)%s \n",p->right->key);
            push(&root,p);
            //peek(root);
            i--;
        }
        //printf("%s ",p->key);
    }
    puts("\nPRE: ");
    preorder(pop(&root));
    /*NodeT *p = createNode("spring");
    push(&root, p);
    p = createNode("summer");
    push(&root, p);
    p = createNode("warm");
    p->left = pop(&root);
    printf("\n%s popped from stack", p->left->key);
    peek(root);
    p->right = pop(&root);
    printf("\n%s popped from stack", p->right->key);
    //peek(root);
    push(&root,p);
    p = createNode("fall");
    push(&root, p);
    p = createNode("winter");
    push(&root, p);*/

    //printf("\n%s popped from stack\n", pop(&root)->key);
    //printf("\n%s popped from stack\n", pop(&root)->key);
    return 0;
}

