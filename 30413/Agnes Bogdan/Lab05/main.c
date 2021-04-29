#include <stdio.h>
#include <stdlib.h>
typedef int KeyType;
typedef int ElementType;
typedef struct node_type
{
    KeyType key;
    ElementType info;
    struct node_type *left, *right;
} BSTNodeT;

void fatalError( const char *msg )
{
    printf( msg );
    printf( "\n" );
    exit ( 1 );
}

void preorder( BSTNodeT *p, int level )
{
    if ( p != NULL )
    {
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->key, level);
    preorder( p->left, level + 1 );
    preorder( p->right, level + 1 );
    }
}

void inorder( BSTNodeT *p, int level )
{
    if ( p != NULL )
    {
    inorder( p->left, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->key, level);
    inorder( p->right, level + 1 );
    }
}
void postorder( BSTNodeT *p, int level )
{
    if ( p != NULL )
    {
    postorder( p->left, level + 1 );
    postorder( p->right, level + 1 );
    for ( int i = 0; i <= level; i++ ) printf( " " );
    printf( "%c %d\n", p->key, level);
    }
}
BSTNodeT *createBinTree()
{
    BSTNodeT *p;
    char c;
    scanf("%c", &c);
    if ( c == '*' )
    return NULL;
    else
    {
    p = ( BSTNodeT *) malloc( sizeof( BSTNodeT ));
    if ( p == NULL )
    fatalError( "Out of space in createBinTree" );
    p->key = c;
    p->left = createBinTree();
    p->right = createBinTree();
    }
    return p;
}

BSTNodeT *createNode(KeyType givenKey)
{
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
    p->key = givenKey;

    p->left = p-> right = NULL;
    }
    return p;
}
BSTNodeT *insertNode(BSTNodeT *root, int key)
{
    if (root == NULL)
    root = createNode(key);
    else
    {
    if ((int)key < (int)root->key)
    root->left = insertNode(root->left, key);
    else if ((int)key > (int)root->key)
    root->right = insertNode(root ->right, key);
    else
    printf("\nNode with key = %c already exists\n", key);
    }
    return root;
}

BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
    return NULL;
    }
    if(node->left)
    return findMin(node->left);
    else
    return node;
}
BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {
    return NULL;
    }
    if(node->right)
    return findMax(node->right);
    else
    return node;
}

BSTNodeT *find(BSTNodeT *root, KeyType givenKey)
{
    if (root == NULL) return NULL;
    for (BSTNodeT *p = root; p != NULL;)
    {
    if (givenKey == p->key) return p;
    else
    if (givenKey < p->key) p = p->left;
    else p = p->right;
    }
    return NULL;
}

BSTNodeT* delNode(BSTNodeT* node, int key)
{
    if(node == NULL)
    {
    printf("Element Not Found");
    }
    else if(key < node->key)
    {
    node->left = delNode(node->left, key);
    }
    else if(key > node->key)
    {
    node->right = delNode(node->right, key);
    }
    else
    {
    if(node->right && node->left)
    {
    BSTNodeT *temp = findMin(node->right);
    node -> key = temp->key;
    node -> right = delNode(node->right, temp->key);
    }
    else
    {
    BSTNodeT *temp = node;
    if(node->left == NULL)
    node = node->right;
    else if(node->right == NULL)
    node = node->left;
    free(temp);
    }
    }
    return node;
}
int main()
{
    char instr[3];
    BSTNodeT *node = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    BSTNodeT *root = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    printf("creating a BT\n");
    root = createBinTree();

    scanf("%s", &instr);
    if (instr[0] == 'i') {
        KeyType key = instr[1];
        node = insertNode(root, key);

    }
    else if (instr[0] == 'd') {
         KeyType key = instr[1];
         node = delNode(root, key);
    }
    else if (instr[0] == 'f') {
         KeyType key = instr[1];
         node = find(root, key);
         if (node != NULL) printf("the node with key %c is found", key);
         else printf("the node with key %c is not found", key);
    }
    else if (instr[0] == 't') {
         if(instr[1] == 'p') preorder(root, 0);
         else if(instr[1] == 'P') postorder(root, 0);
         else if(instr[1] == 'i') inorder(root, 0);
    }
    else if (instr[0] == 'g') {
        if(instr[1] == 'm') {
            node = findMin(root);
            printf("the minimum is: %c", node->key);
        }
         else if(instr[1] == 'M') {
            node = findMax(root);
            printf("the maximum is: %c", node->key);
         }
    }
    return 0;
}
