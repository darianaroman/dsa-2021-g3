#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    char old;
    struct node *left, *right;
} NodeT;

NodeT *createBinTree( int branch, NodeT *parent )
{
    NodeT *p;
    int id;

    if( branch==0 ) printf("Root identifier [0 to end] = ");
       else if( branch==1 ) printf("Left child of %d [0 to end] = ", parent->old);
               else printf("Right child of %d [0 to end] = ", parent->old);
    scanf("%d", &id);
    if( id==0 ) return NULL;
       else {
              p= (NodeT *)malloc(sizeof(NodeT));
              if( p==NULL ) printf("Out of space");
              p->old= id;
              p->left= createBinTree(1, p);
              p->right= createBinTree(2, p);
            }
    return p;
}

int TeamTenure(NodeT *p, int k, int s) ///k=nr of nodes under p
{
    if( p!=NULL )
    {
        s+=p->old;
        if( p->left!=NULL ) k++;
        if( p->right!=NULL ) k++;
        TeamTenure(p->left, k, s);
        TeamTenure(p->right, k, s);
    }
}

}

int main()
{

    return 0;
}
