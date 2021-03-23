#include <stdio.h>
#include <stdlib.h>

int orderRomanNumbers(char a, char b)
{
    if(a=='M' && b!='M') return 1;
    if(a=='D' && b!='M' && b!='D') return 1;
    if(a=='C' && b!='M' && b!='D' && b!='C') return 1;
    if(a=='L' && b!='M' && b!='D' && b!='C' && b!='L') return 1;
    if(a=='X' && b!='M' && b!='D' && b!='C' && b!='L' && b!='X') return 1;
    if(a=='V' && b!='M' && b!='D' && b!='C' && b!='L' && b!='X' && b!='V') return 1;
    if(a==b) return 0;
    return -1;
}
typedef struct bst_node
{
    char key;
    struct bst_node *left, *right;
}BSTNodeT;
BSTNodeT *createNode(char givenKey)
{
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof(BSTNodeT));
    if(p)
    {
        p->key=givenKey;
        p->left = p->right = NULL;
    }
    return p;
}
BSTNodeT *recInsert(BSTNodeT *root, char key)
{
    if(root == NULL) root = createNode(key);
    else
    {
        if(orderRomanNumbers(key, root->key) == -1) root->left = recInsert(root->left, key);
        else if(orderRomanNumbers(key, root->key) == 1) root->right = recInsert(root->right, key);
        else printf("\nNode already exists\n");
    }
    return root;
}
BSTNodeT *find(BSTNodeT *root, char key)
{
    BSTNodeT *p;
    if(root==NULL) return NULL;
    p=root;
    while(p!=NULL)
    {
        if(p->key==key) return p;
        else
        {
            if(orderRomanNumbers(key,p->key)==-1) p=p->left;
            else p=p->right;
        }
    }
    return NULL;
}
BSTNodeT *findMin(BSTNodeT*node)
{
    if (node == NULL) return NULL;
    if(node->left) return findMin(node->left);
    else return node;
}
BSTNodeT *findMax(BSTNodeT*node)
{
    if (node == NULL) return NULL;
    if(node->right) return findMax(node->right);
    else return node;
}
BSTNodeT *delNode(BSTNodeT *node, char key, FILE * file)
{
    if(node == NULL) fprintf(file, "Element not found\n");
    else if(orderRomanNumbers(key,node->key)==-1) node->left=delNode(node->left,key, file);
    else if(orderRomanNumbers(key,node->key)==1) node->right=delNode(node->right,key, file);
    else
    {
        if(node->right && node->left)
        {
            BSTNodeT *temp = findMin(node->right);
            node->key = temp->key;
            node->right=delNode(node->right, temp->key, file);
        }
        else
        {
            BSTNodeT *temp = node;
            if(node->left==NULL) node=node->right;
            else if (node->right == NULL) node = node->left;
            free(temp);
        }
    }
    return node;
}

void preorder(BSTNodeT *p, FILE * file)
{
    if( p!= NULL )
    {
        fprintf(file, "%c", p->key);
        preorder(p->left, file);
        preorder(p->right, file);
    }
}
void inorder(BSTNodeT *p, FILE * file)
{
    if( p!= NULL )
    {
        inorder(p->left, file);
        fprintf(file, "%c", p->key);
        inorder(p->right, file);
    }
}
void postorder(BSTNodeT *p, FILE * file)
{
    if( p!= NULL )
    {
        postorder(p->left, file);
        postorder(p->right, file);
        fprintf(file, "%c", p->key);
    }
}
int main(int argc, char *argv[])
{
    FILE * fin = fopen(argv[1], "r");
    FILE * fout = fopen(argv[2], "w");
    BSTNodeT *root=(BSTNodeT*)malloc(sizeof(BSTNodeT));
    root=NULL;
    char c1,c2;
    fscanf(fin, "%c %c", &c1, &c2);
    while(c1 != '\n' && c2 != '\n')
    {
        if(c1 == 'i')
        {
            if(root == NULL) root = recInsert(root, c2);
            else recInsert(root, c2);
        }
        else if (c1 == 'd')
        {
            fprintf(fout, "\nDeleted node with the key %c", c2);
            delNode(root, c2, fout);
        }
        else if(c1 == 'f') find(root, c2);
        else if(c1 == 't')
        {
            if(c2 == 'p')
            {
                fprintf(fout, "\nThe preorder traversal of the tree is: ");
                preorder(root, fout);
            }
            if(c2 == 'P')
            {
                fprintf(fout, "\nThe postorder traversal of the tree is: ");
                postorder(root, fout);
            }
            if(c2 == 'i')
            {
                fprintf(fout, "\nThe inorder traversal of the tree is: ");
                inorder(root, fout);
            }
        }
        else if(c1 == 'g')
        {
            if(c2 == 'm')
            {
                BSTNodeT *p=findMin(root);
                fprintf(fout, "\nThe minimum node is: %c", p->key);
            }
            else if(c2 == 'M')
            {
                BSTNodeT *p=findMax(root);
                fprintf(fout, "\nThe maximum node is: %c", p->key);
            }
        }
        else fprintf(fout, "Command not defined!\n");
        fscanf(fin, "%c", &c1); // reading the space
        fscanf(fin , "%c %c", &c1, &c2);
    }
    return 0;
}
