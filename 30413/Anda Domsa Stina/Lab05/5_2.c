#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define LEFT 1
#define RIGHT 2
typedef struct bst_node
{
    char key;
    struct bst_node *left, *right;
} BSTNodeT;
BSTNodeT *root=NULL;
BSTNodeT *Insert(BSTNodeT *root, char key)
{
    BSTNodeT *p;

    if (root == NULL)
    {
        p = (BSTNodeT *) malloc(sizeof(BSTNodeT));
        p->key = key;
        p->left = p->right = NULL;
        root = p;
        return root;
    }
    else
    {
        if (key < root->key)
            root->left = Insert(root ->left, key);
        else if (key > root->key)
            root->right = Insert(root ->right, key);
        else /* key already there */
            printf("\nNode of key=%d already exists\n",
                   key);
    }
    return root;
}
void preorder( BSTNodeT *p, int level )
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        printf( "%c\n", p->key );
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
    }
}
void inorder(BSTNodeT *p, int level)
{
    int i;

    if (p != NULL)
    {
        inorder(p->left, level + 1);
        for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
        printf("%c\n", p->key);
        inorder(p->right, level + 1);
    }
}
void postorder(BSTNodeT *p, int level)
{
    int i;

    if (p != NULL)
    {
        postorder(p->left, level + 1);
        postorder(p->right, level + 1);
        for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
        printf("%c\n", p->key);
    }
}
BSTNodeT *find(BSTNodeT *root, char key)
{
    BSTNodeT *p;

    if (root == NULL) return NULL;
    p = root;
    while (p != NULL)
    {
        if (p -> key == key)
            return p; /* found */
        else if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    return NULL; /* not found */
}
BSTNodeT *delNode(BSTNodeT *root, char key)
{
    BSTNodeT *p; /* points to node to delete */
    BSTNodeT *pParent; /* points to parent of p */
    BSTNodeT *pRepl; /* points to node that will replace p */
    BSTNodeT *pReplParent; /* points to parent of node that will replace p */
    int direction; /* LEFT, RIGHT */
    if (root == NULL) return NULL; /* empty tree */
    p = root;
    pParent = NULL;
    while (p != NULL && p->key != key)
    {
        if (key < p->key)
        {
            /* search left branch */
            pParent = p;
            p = p->left;
            direction = LEFT;
        }
        else
        {
            /* search right branch */
            pParent = p;
            p = p->right;
            direction = RIGHT;
        }
    }
    if (p == NULL)
    {
        printf("\nNo node of key value=%d\n", key);
        return root;
    }
    /* node of key p found */
    if (p->left == NULL)
        pRepl = p->right; /* no left child */
    else if (p->right == NULL)
        pRepl = p->left; /* no right child */
    else
    {
        /* both children present */
        pReplParent = p;
        pRepl = p->right; /* search right subtree */
        while (pRepl->left != NULL)
        {
            pReplParent = pRepl;
            pRepl = pRepl->left;
        }
        if (pReplParent != p)
        {
            pReplParent->left = pRepl->right;
            pRepl->right = p->right;
        }
        pRepl->left = p->left;
    }
    free(p);
    printf("\nDeletion of node %c completed\n", key);
    if (pParent == NULL)
        return pRepl; /* original root was deleted */
    else
    {
        if (direction == LEFT)
            pParent->left = pRepl;
        else
            pParent->right = pRepl;
        return root;
    }
}
int minValue(BSTNodeT* root)
{
    BSTNodeT* current = root;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
    {
        current = current->left;
    }
    return(current->key);
}
int maxValue(BSTNodeT* root)
{
     BSTNodeT* current = root;

    /* loop down to find the rightmost leaf */
    while (current->right != NULL)
    {
        current = current->right;
    }
    return(current->key);
}
int main()
{
    char c, key;
    char min, max;
    do
    {
        c=getchar();
        //printf("%c",c);
        if(c=='i')
        {
            key=getchar();
            //printf("%c",key);
            root = Insert(root,key);

        }
        if(c=='t')
        {
            c=getchar();

            if(c=='p')
            {
                preorder(root,0);
            }
            if(c=='P')
            {
                postorder(root,0);
            }
            if(c=='i')
            {
                inorder(root,0);
            }
        }
        if(c=='f')
        {
            key=getchar();
            if(find(root,key)==NULL)
            {
                printf("\n Node %c not found \n", key);
            }
            else
            {
                printf("\n Node %c found \n", key);
            }
        }
        if(c=='d')
        {
            key=getchar();
            if(find(root,key)!=NULL)
            {
                delNode(root,key);
            }
        }
        if(c=='g')
        {
            c=getchar();
            if(c=='m')
            {
                min=minValue(root);
                printf("%c", min);
            }
            if(c=='M')
            {
                max=maxValue(root);
                printf("%c", max);
            }
        }
    }while(c!='x');
    return 0;
}
