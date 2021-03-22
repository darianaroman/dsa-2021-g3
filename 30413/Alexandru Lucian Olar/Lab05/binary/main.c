#include <stdio.h>
#include <stdlib.h>


#define LEFT 1
#define RIGHT 2


FILE *input, *output;


typedef struct bst_node
{
  char alfa;
  struct bst_node *left;
  struct bst_node *right;

} BSTNodeT;


void preorder(BSTNodeT *p, int level)
{
  int i;

  if (p != NULL)
  {
    for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
    fprintf(output,"%c", p->alfa);
    preorder(p->left, level + 1);
    preorder(p->right, level + 1);
  }
}

void inorder(BSTNodeT *p, int level)
{
  int i;

  if (p != NULL)
  {
    for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
    preorder(p->left, level + 1);
    fprintf(output,"%c", p->alfa);
    preorder(p->right, level + 1);
  }
}

void postorder(BSTNodeT *p, int level)
{
  int i;

  if (p != NULL)
  {
    for (i = 0; i <= level; i++) printf(" "); /* for nice listing */
    preorder(p->left, level + 1);
    preorder(p->right, level + 1);
    fprintf(output,"%c", p->alfa);
  }

}

BSTNodeT *recInsert(BSTNodeT *root, char alfa)
{
  BSTNodeT *p;

  if (root == NULL)
  {
    p = (BSTNodeT *) malloc(sizeof(BSTNodeT));
    p->alfa = alfa;
    p->left = p->right = NULL;
    root = p;
    return root;
  }
  else
  {
    if (alfa < root->alfa)
      root->left = recInsert(root ->left, alfa);
    else
    if (alfa > root->alfa)
      root->right = recInsert(root ->right, alfa);
    else /* the char already there */
      fprintf(output ,"\nNode %c already exists\n",
              alfa);
  }
  return root;
}

BSTNodeT *find(BSTNodeT *root, int alfa)
{
  BSTNodeT *p;

  if (root == NULL) return NULL;
  p = root;
  while (p != NULL)
  {
    if (p -> alfa == alfa)
      return p; /* found */
    else
    if (alfa < p->alfa)
	  p = p->left;
    else
	  p = p->right;
  }
  return NULL; /* not found */
}


BSTNodeT* findMin(BSTNodeT *root)
{
    if(root == NULL)
        return NULL;
    else
        if (root->left)
            return findMin((root->left));
        else
            return root;
}

BSTNodeT* findMax(BSTNodeT* root)
{
    if(root == NULL)
        return NULL;
    else
        if (root->right)
            return findMax((root->right));
        else
            return root;
}

BSTNodeT *delNode(BSTNodeT *root, char alfa)
{
  BSTNodeT *p;
  BSTNodeT *pParent;
  BSTNodeT *pRepl;
  BSTNodeT *pReplParent;
  int direction;
  if (root == NULL) return NULL;
  p = root;
  pParent = NULL;
  while (p != NULL && p->alfa != alfa)
  {
    if (alfa < p->alfa)
    {
      pParent = p;
      p = p->left;
      direction = LEFT;
    }
    else
    {
      pParent = p;
      p = p->right;
      direction = RIGHT;
    }
  }
  if (p == NULL)
  {
    fprintf(output, "\nNo node %c\n", alfa);
    return root;
  }

  if (p->left == NULL)
    pRepl = p->right;
  else
  if (p->right == NULL)
    pRepl = p->left;
  else
  {
    pReplParent = p;
    pRepl = p->right;
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
  fprintf(output ,"\nDeletion of node %c completed\n", alfa);
  if (pParent == NULL)
    return pRepl;
  else
  {
    if (direction == LEFT)
      pParent->left = pRepl;
    else
      pParent->right = pRepl;
    return root;
  }
}

int main()
{

    BSTNodeT *root = NULL;
    BSTNodeT *finder = NULL;

    FILE *input = fopen("date.in", "r");
    FILE *output = fopen("date.out", "w");


    char *command = (char *)malloc(100 * sizeof(char));

    while (!feof(input)) {
        fgets(command, 100, input);
        switch (command[0]) {
            case 'i':
                root = recInsert(root, command[1]);
                break;
            case 'd':
                root = delNode(root, command[1]);
                break;
            case 'f':
                {
                    finder = find(root, command[1]);
                    if ( finder == NULL)  fprintf(output,"\n not found %c \n", command[1]);
                    else  fprintf(output,"\n found %c \n", command[1]);
                }

                break;
            case 't':
                {
                    if(command[1]=='p') preorder(root, 0);
                    if(command[1]=='P') postorder(root, 0);
                    if(command[1]=='i') inorder(root, 0);
                }
                break;

            case 'g':
            {
                    if(command[1] == 'm')
                    {
                        finder=findMin(root);
                        fprintf(output,"\n the minimum node is %c \n", finder->alfa);
                    }
                    if(command[1] == 'M')
                    {
                        finder=findMax(root);
                        fprintf(output,"\n the maximum node is %c \n", finder->alfa);
                    }


            }


            default:
                fprintf(output, "Wrong mode selected\n");
        }
    }

    free(command);
    fclose(input);
    fclose(output);
    return 0;
}
