#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LEFT 1
#define RIGHT 2

typedef struct bst_node
{
  int key;
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
void preorder(BSTNodeT *p, int level, FILE *g)
{
  int i;

  if (p != NULL)
  {
    for (i = 0; i <= level; i++) fprintf(g, " "); /* for nice listing */
    fprintf(g, "%c\n", p->key);
    preorder(p->left, level + 1, g);
    preorder(p->right, level + 1, g);
  }
}
void inorder(BSTNodeT *p, int level, FILE *g)
{
  int i;

  if (p != NULL)
  {
    inorder(p->left, level + 1, g);
    for (i = 0; i <= level; i++) fprintf(g, " "); /* for nice listing */
    fprintf(g, "%c\n", p->key);
    inorder(p->right, level + 1, g);
  }
}
void postorder(BSTNodeT *p, int level, FILE *g)
{
  int i;

  if (p != NULL)
  {
    postorder(p->left, level + 1, g);
    postorder(p->right, level + 1, g);
    for (i = 0; i <= level; i++) fprintf(g," "); /* for nice listing */
    fprintf(g,"%c\n", p->key);
  }
}
/* non recursive version of insert */

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
      root->left = recInsert(root ->left, key);
    else
    if (key > root->key)
      root->right = recInsert(root ->right, key);
    else /* key already there */
      printf("\nNode of key=%d already exists\n",
              key);
  }
  return root;
}

BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {   /* There is no element in the tree */
        return NULL;
    }
    if(node->left) /* Go to the left sub tree to find the min element */
        return findMin(node->left);
    else
        return node;
}

BSTNodeT *findMax(BSTNodeT *node)
{
    if(node == NULL)
    {   /* There is no element in the tree */
        return NULL;
    }
    if(node->right) /* Go to the left sub tree to find the min element */
        return findMax(node->right);
    else
        return node;
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
    else
    if (key < p->key)
	  p = p->left;
    else
	  p = p->right;
  }
  return NULL; /* not found */
}
BSTNodeT *delNode(BSTNodeT *root, char key, FILE *g)
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
    fprintf(g,"\nNo node of key value=%d\n", key);
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
  fprintf(g,"\nDeletion of node %c completed\n", key);
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
int getInt(const char *message)
{
    int val;
    printf(message);
    scanf("%d", &val);
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
int main(int argc, char *argv[])
{
    BSTNodeT *p;
    int n;
    char key;
    FILE *f = fopen(argv[1], "r");
    FILE *g = fopen(argv[2], "a");

    fscanf(f,"%d", &n);

    root = NULL;

    size_t linesz = 20;
    char *line = malloc(linesz *sizeof(char));
    if(!line)
    {
        printf("error alocating memory");
        exit(0);
    }

    while (fgets(line, linesz, f))
    {
        switch(line[0])
        {
            case 'i':
            {
                root = recInsert(root, line[1]);
                break;
            }
            case 'd':
            {
                root = delNode(root, line[1],g);
                break;
            }
            case 'f':
            {
                BSTNodeT *p = find(root, line[1]);
                if(p!=NULL)
                    fprintf(g,"found %c\n", p->key);
                else
                    fprintf(g,"not found %c\n", line[1]);

                break;
            }
            case 't':
            {
                if(line[1] == 'p')
                {
                    fprintf(g, "Preorder:\n");
                    preorder(root, 0, g);
                    fprintf(g,"\n");
                }
                else if(line[1] == 'P')
                {
                    fprintf(g, "Postorder:\n");
                    postorder(root, 0, g);
                    fprintf(g,"\n");
                }
                else if(line[1] == 'i')
                {
                    fprintf(g, "Inorder:\n");
                    inorder(root, 0, g);
                    fprintf(g,"\n");
                }
                else printf("Unknown instruction %c", line[1]);

                break;
            }
            case 'g':
            {
                BSTNodeT *q;
                if(line[1] == 'm')
                {
                    q = findMin(root);
                    if(q!=NULL)
                        fprintf(g,"min is %c\n", q->key);
                    else
                        fprintf(g,"error min");
                }
                else if ( line[1] == 'M')
                {
                    q = findMax(root);
                    if(q!=NULL)
                        fprintf(g,"max is %c\n", q->key);
                    else
                        fprintf(g,"error max");
                }
                else printf("Unknown instruction %c", line[1]);
                break;
            }
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
