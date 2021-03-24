#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *input;
FILE *output;

//typedef int KeyType;
typedef int ElementType;

typedef struct node_type
{
  //KeyType key;
  char *key;
  //ElementType info;
  struct node_type *left, *right;
} BSTNodeT;

BSTNodeT *createNode(char *givenKey)
{
    /* build node */
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p)
    {
        strcpy(p->key, givenKey);//p->key = givenKey;
        /* the info field should be filled in here */
        p->left = p-> right = NULL; /* leaf node */
    }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char *key)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
        root = createNode(key);
    else
    {
        if (strcasecmp(key,root->key)==-1)
            root->left = insertNode(root->left, key);
        else if (strcasecmp(key,root->key)==1)
            root->right = insertNode(root ->right, key);
        else
            fprintf(output, "\nNode with key = %d already exists\n", key);
    }
    return root;
}

BSTNodeT *delNode(BSTNodeT *root, char* key)
{
  BSTNodeT *p; /* points to node to delete */
  BSTNodeT *pParent; /* points to parent of p */
  BSTNodeT *pRepl; /* points to node that will replace p */
  BSTNodeT *pReplParent; /* points to parent of node that will replace p */
  int direction; /* LEFT, RIGHT */
  if (root == NULL) return NULL; /* empty tree */
  p = root;
  pParent = NULL;
  while (p != NULL && strcasecmp(key,p->key)!=0)
  {
    if (strcasecmp(key,p->key)==-1)
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
    fprintf(output, "\nNo node of key value=%d\n", key);
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
  fprintf(output, "\nDeletion of node %d completed\n", key);
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

BSTNodeT *find(BSTNodeT *root, char *key)
{
  BSTNodeT *p;

  if (root == NULL) return NULL;
  p = root;
  while (p != NULL)
  {
    if (strcasecmp(key,p->key) == 0)
      return p; /* found */
    else
    if (strcasecmp(key,p->key) == -1)
	  p = p->left;
    else
	  p = p->right;
  }
  return NULL; /* not found */
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

void preorder(BSTNodeT *p)
{
  if (p != NULL)
  {
    /* include code for info retrieval here */
    fprintf(output, "%s\n", p->key );
    preorder(p->left);
    preorder(p->right);
  }
}

void inorder(BSTNOdeT *p)
{
  if (p != NULL)
  {
    inorder(p->left);
    fprintf(output, "%s\n", p->key );
    /* include code for info retrieval here */
    inorder(p->right);
  }
}

void postorder(BSTNOdeT *p)
{
  if (p != NULL)
  {
    postorder(p->left);
    postorder(p->right);
    fprintf(output, "%s\n", p->key );
    /* include code for info retrieval here */
  }
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

void read(BSTNodeT *root,char *cmd)//if command * thenends//cmd=command
{
    while(strcmp(cmd, "*") != 0  &&  fscanf(input,"%s",command) != EOF)//program ends when providing *
    {

        fprintf(output, "Press *+Enter to exit./Provide * to exit" );
        //printf("%s",c);
        //process info
        switch(cmd[0])
        {
            case 'i':
                //insert
                if(!insertNode(root,cmd[1]))
                {
                    fprintf(output, "Problem when inserting node with key %s\n", cmd[1])
                }
                break;

            case 'd':
                //delete
                if(!delNode(root,cmd[1]);)
                {
                    fprintf(output, "Problem when deleting node with key %s\n", cmd[1])
                }
                break;

            case 'f':
                //find but use strcasecmp to avoid confusion
                BSTNodeT *p;
                p=find(root, cmd[1])
                if(!p)
                {
                    fprintf(output, "Node with key %s not found\n", cmd[1]);
                }
                else
                {
                    fprintf(output, "Node with key %s was found\n", cmd[1]);
                }
                break;

            case 't':
                //transversals
                if(strcasecmp(cmd[1],"i")==0)
                {
                    //inorder
                    fprintf(output, "Inorder transversal\n");
                    inorder(root);
                }
                if(strcmp(cmd[1],"P")==0)//can't use case cmp
                {
                    //postorder
                    fprintf(output, "Postorder transversal\n");
                    postorder(root);
                }
                if(strcmp(cmd[1],"p")==0)//can't use case cmp
                {
                    //preorder
                    fprintf(output, "Preorder transversal\n");
                    preorder(root);
                }
                break;

            case 'g':
                //provide min=m/max=M
                if(strcmp(cmd[1],"m")==0)//can't use case cmp
                {
                    //min
                    BSTNodeT *p;
                    p=findMin(root, cmd[1])
                    if(!p)
                    {
                        fprintf(output, "Empty\n");
                    }
                    else
                    {
                        fprintf(output, "Minimum was found: %s\n", p->key);
                    }

                }
                if(strcmp(cmd[1],"M")==0)//can't use case cmp
                {
                    //max
                    BSTNodeT *p;
                    p=findMax(root, cmd[1])
                    if(!p)
                    {
                        fprintf(output, "Empty\n");
                    }
                    else
                    {
                        fprintf(output, "Maximum was found: %s\n", p->key);
                    }

                }
                break;

            // operator doesn't match any case constant +, -, *, /
            default:
                fprintf(output, "Error! input is not correct");
        }
    }
}

//use casecmp when finding node
int main(int argv, char *argc[])
{
    BSTNodeT *root;
    char* command;

    root = NULL;

    input=fopen(argv[1], "r");
    output=fopen(argv[2], "w");

    if(argc==1)
    {
        printf("Please provide the command line arguments");
        return 0;
    }
    read(root,cmd);
    return 0;
}
