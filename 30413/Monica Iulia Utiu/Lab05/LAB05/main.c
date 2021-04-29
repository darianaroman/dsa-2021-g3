
//----- Listing.5.9 --- Code part 09 ----------------------
// Binary search trees code sample.}
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

BSTNodeT *root;

void fatalError(const char *msg)
{
 printf(msg);
 printf("\n");
 exit (1);
}

/* Tree traversal functions
 * p = current node;
 * level = used for nice printing
*/
void preorder(BSTNodeT *p, int level)
{
  int i;

  if (p != NULL)
  {
    for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
    printf("%2c\n", p->key);
    preorder(p->left, level + 1);
    preorder(p->right, level + 1);
  }
}
void inorder(BSTNodeT *p, int level)
{
  int i;

  if (p != NULL)
  {
    inorder(p->left, level + 1);
    for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
    printf("%2c\n", p->key);
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
    printf("%2c\n", p->key);
  }
}

BSTNodeT *recInsert(BSTNodeT *root, char key)
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
      root->left = recInsert(root->left, key);
    else
    if (key > root->key)
      root->right = recInsert(root->right, key);
    else /* key already there */
      printf("\nNode of key=%c already exists\n",key);
  }
  return root;
}
BSTNodeT *find(BSTNodeT *root, char key)
{
  BSTNodeT *p;

  if (root == NULL) return NULL;
  p = root;
  while (p != NULL)
  {
    if ( p->key == key )
      return p; /* found */
    else
    if ( key < p->key )
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
    { /* search left branch */
      pParent = p;
      p = p->left;
      direction = LEFT;
    }
    else
    { /* search right branch */
      pParent = p;
      p = p->right;
      direction = RIGHT;
    }
  }
  if (p == NULL)
  {
    printf("\nNo node of key value=%c\n", key);
    return root;
  }
  /* node of key p found */
  if (p->left == NULL)
    pRepl = p->right; /* no left child */
  else
  if (p->right == NULL)
    pRepl = p->left; /* no right child */
  else
  { /* both children present */
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
void delTree(BSTNodeT *root)
{
  if (root != NULL)
  {
    delTree(root->left);
    delTree(root->right);
    free(root);
  }
}
int getChar(const char *message)
{
    char val;
    printf(message);
    scanf("%c", &val);
    fflush(stdin);
    return val;
}
char prompt(const char *message)
{
    printf(message);
    char ch = getchar();
    fflush(stdin);
    return ch;
}

BSTNodeT *minim(BSTNodeT *p)
{
  if(p->left==NULL) return p;
     else minim(p->left);
}

BSTNodeT *maxim(BSTNodeT *p)
{
  if(p->right==NULL) return p;
     else maxim(p->right);
}

int main()
{
  BSTNodeT *p;
  int n;
  char  ch, action[3], key;

  printf("Number of nodes to insert= ");
  scanf("%d", &n);
  root = NULL;
  printf("Input keys: ");
  for (int i = 0; i < n+1; i++)
  {
    scanf("%c ",&key);
    root = recInsert(root, key);
  }
  getc(stdin);
  printf("\nPress enter to see commands\n");

  while(getc(stdin) != 'q') {

  printf("\n   - i<letterOfNode> to insert node ");
  printf("\n   - d<letterOfNode> to delete node ");
  printf("\n   - f<letterOfNode> to find node ");
  printf("\n   - tp to print tree in preorder  ");
  printf("\n   - ti to print tree in inorder  ");
  printf("\n   - tP to print tree in postorder  ");
  printf("\n   - gm to print minimum node of tree ");
  printf("\n   - gM to print maximum node of tree\n ");
  printf("\nCommand: ");

  scanf("%s",&action);
  switch(action[0])
  {
      case 'i': root = recInsert(root, action[1]);
                break;
      case 'd': root = delNode(root, action[1]);
                break;
      case 'f': p = find(root, action[1]);
                if ( p != NULL )
                    printf("Node %c found\n",p->key);
                    else printf("Node %c NOT found\n",p->key);
                break;
      case 't':  if( action[1] == 'p' )
                 {
                    printf("\nPreorder listing\n");
                    preorder(root, 0);
                 }
                 if( action[1] == 'P' )
                 {
                     printf("\nPostorder listing\n");
                     postorder(root, 0);
                 }
                 if( action[1] == 'i' )
                 {
                     printf("\nInorder listing\n");
                     inorder(root, 0);
                 }
                 break;
      case 'g': if( action[1] == 'm' )
                {
                    p = minim(root);
                    printf("Minimum node key is: %c",p->key);
                }
                else if( action[1] == 'M' )
                     {
                         p = maxim(root);
                         printf("Maximum node key is: %c",p->key);
                     }
                break;
  }
      printf("\nPress Q to exit or enter to continue");
      printf("\n\n");
  }

}
