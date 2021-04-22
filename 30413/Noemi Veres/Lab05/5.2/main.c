#include <stdio.h>
#include <stdlib.h>
/// open a file (if possible)
FILE *openCheck (const char *path, const char *mode)
{
    FILE *pf = fopen(path,mode);
    if (pf == NULL)
    {
        puts("cannot open the file");
        exit(1);
    }
    return pf;
}
/// node type
typedef struct node_type
{
    char key;
    struct node_type *left, *right;
} BSTNodeT;
/// create a node
BSTNodeT *createNode(char givenKey)
{
    /* build node */
    BSTNodeT *p = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if (p)
    {
        p->key = givenKey;
        /* the info field should be filled in here */
        p->left = p->right = NULL; /* leaf node */
    }
    return p;
}
/// recursive insert
BSTNodeT *insertNode(FILE *pOut, BSTNodeT *root, char key)
{
    /* If the tree is empty, then a single node tree is created */
    if (root == NULL)
        root = createNode(key);
    else
    {
        if (key < root->key)
            root->left = insertNode(pOut,root->left,key);
        else if (key > root->key)
            root->right = insertNode(pOut,root ->right,key);
        else
            fprintf(pOut,"\nNode with key = %c already exists\n", key);
    }
    return root;
}
/// find a node with a given key
BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if (root == NULL) return NULL; /* empty tree */
    for (BSTNodeT *p = root; p != NULL;)
    {
        if (givenKey == p->key)
            return p;
        else if (givenKey < p->key)
        p = p->left;
        else p = p->right;
    }
    return NULL; /* not found */
}
/// find minimum/maximum key value
BSTNodeT *findMin(BSTNodeT *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
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
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->right) /* Go to the left sub tree to find the min element */
        return findMax(node->right);
    else
        return node;
}
/// delete a node with a given key
BSTNodeT* delNode(FILE *pOut, BSTNodeT* node, char key)
{
    if(node == NULL)
    {
        fprintf(pOut,"Element '%c' Not Found",key);
    }
    else if(key < node->key)
    {
        // must be in left subtree
        node->left = delNode(pOut, node->left, key);
    }
    else if(key > node->key)
    {
        // must be in right subtree
        node->right = delNode(pOut, node->right, key);
    }
    else
    {
        // found node
        /* Now We can delete this node and replace with either minimum element
           in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            BSTNodeT *temp = findMin(node->right);
            node -> key = temp->key;
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = delNode(pOut, node->right, temp->key);
        }
        else
        {
            /* If there is only one or zero children then we can directly
               remove it from the tree and connect its parent to its child */
            BSTNodeT *temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp); /* temp is no longer required */
        }
    }
    return node;
}
/// traversals
void preorder(FILE *pOut, BSTNodeT *p)
{
    if (p != NULL)
    {
        fprintf(pOut,"%c",p->key);
        preorder(pOut,p->left);
        preorder(pOut,p->right);
    }
}
void inorder(FILE *pOut, BSTNodeT *p)
{
    if (p != NULL)
    {
        preorder(pOut,p->left);
        fprintf(pOut,"%c",p->key);
        preorder(pOut,p->right);
    }
}
void postorder(FILE *pOut, BSTNodeT *p)
{
    if (p != NULL)
    {
        preorder(pOut,p->left);
        preorder(pOut,p->right);
        fprintf(pOut,"%c",p->key);
    }
}
int main(int argc, char *argv[])
{
    BSTNodeT *root = NULL, *p = NULL;
    FILE *pIn = openCheck(argv[1], "r");
    FILE *pOut = openCheck(argv[2], "w");
    int f = fgetc(pIn), ch;
    while(f != EOF)
    {
        ch = fgetc(pIn);
        switch(f)
        {
        case 'i':
        {
            root = insertNode(pOut,root,ch);
            break;
        }
        case 'd':
        {
            root = delNode(pOut,root,ch);
            break;
        }
        case 'f':
        {
            p = find(root,ch);
            fprintf(pOut,"\nfound it at address: %d",p);
            break;
        }
        case 't':
        {
            putchar('\n');
            switch(ch)
            {
            case 'p':
                fputs("\nPRE: ",pOut);
                preorder(pOut,root);
                break;
            case 'P':
                fputs("\nIN: ",pOut);
                postorder(pOut,root);
                break;
            case 'i':
                fputs("\nPOST: ",pOut);
                inorder(pOut,root);
                break;
            default:
                fprintf(pOut,"\nInvalid operation '%c' for traversal",ch);
                exit(2);
            }
            break;
        }
        case 'g':
        {
            switch(ch)
            {
            case 'm':
                p = findMin(root);
                fprintf(pOut,"\nMinimum is: %c",p->key);
                break;
            case 'M':
                p = findMax(root);
                fprintf(pOut,"\nMinimum is: %c",p->key);
                break;
            default:
                fprintf(pOut,"\nInvalid operation '%c' for get",ch);
                exit(2);
            }
            break;
        }
        default:
            fprintf(pOut,"\nInvalid operation '%c'",f);
            exit(2);
        }
        ch = fgetc(pIn);
        f = fgetc(pIn);
    }
    fclose(pIn);
    fclose(pOut);
    return 0;
}
