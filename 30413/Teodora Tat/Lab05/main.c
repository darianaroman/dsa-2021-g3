#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct node
    {char key;
    int info;
    struct node *left,*right;
} bst_node;
bst_node *createNode(char key)
{

bst_node *p = (bst_node *) malloc (sizeof (bst_node));
if (p)
{
p->key=key;
p->left = p-> right = NULL;
}
return p;
}
void preorder(bst_node *p, FILE *fo)
{
    if (p != NULL)
    {
        fprintf(fo, "%c ", p->key );
        preorder(p->left, fo);
        preorder(p->right, fo);
    }
}
void inorder(bst_node *p, FILE *fo)
{
    if (p != NULL)
    {
        inorder(p->left, fo);
        fprintf(fo, "%c ", p->key );
        inorder(p->right, fo);
    }
}
void postorder(bst_node *p, FILE *fo)
{
    if (p != NULL)
    {
        postorder(p->left, fo);
        postorder(p->right, fo);
        fprintf(fo, "%c ", p->key );
    }
}
bst_node *insertNode(bst_node *root, char key,FILE *fo)
{
    if (root == NULL)
        root = createNode(key);//create one node if it's empty//
    else
    {
        if (key < root->key)
            root->left = insertNode(root->left, key,fo);
        else if (key > root->key)
            root->right = insertNode(root ->right, key,fo);
        else
            printf("\n Node with key = %c already exists\n", key);
    }
    return root;
}
bst_node *findNode(bst_node *root, char givenKey)
{
    if (root == NULL) return NULL; /* empty tree */
    bst_node *p;
    for (p = root; p != NULL;)
    {
        if (givenKey == p->key) return p;
        else if (givenKey < p->key) p = p->left;
        else                   p = p->right;
    }
    return NULL; /* not found */
}


bst_node *findMin(bst_node *node)
{
    if(node == NULL)
    {
        /* There is no element in the tree */
        return NULL;
    }
    if(node->left!=NULL) /* Go to the left sub tree to find the min element */
        return findMin(node->left);

    else
        return node;
}

bst_node *findMax(bst_node *node)
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

bst_node* delNode(bst_node* node, char key, FILE *fo)
{
    if(node == NULL)
    {
        printf(fo,"Element Not Found\n");
    }
    else if(key < node->key)
    {
        // must be in left subtree
        node->left = delNode(node->left, key, fo);
    }
    else if(key > node->key)
    {
        // must be in right subtree
        node->right = delNode(node->right, key, fo);
    }
    else
    {
        // found node
        /* Now We can delete this node and replace with either minimum element
           in the right sub tree or maximum element in the left subtree */
        if(node->right && node->left)
        {
            /* Here we will replace with minimum element in the right sub tree */
            bst_node *temp = findMax(node->left);
            node -> key = temp->key;
            /* As we replaced it with some other node, we have to delete that node */
            node -> right = delNode(node->right, temp->key, fo);
        }
        else
        {
            /* If there is only one or zero children then we can directly
               remove it from the tree and connect its parent to its child */
            bst_node *temp = node;
            if(node->left == NULL)
                node = node->right;
            else if(node->right == NULL)
                node = node->left;
            free(temp); /* temp is longer required */
        }
    }
    return node;
}
void commands(char instruction, char character, bst_node *root, FILE *fo)
{
    switch (instruction)
    {
    case 'i':
        if(root->key==' ')
            root->key=character; ///i'm managing finding the root of the tree
        else
            insertNode(root,character,fo);
        break;
    case 'd':
        delNode(root, character, fo);
        break;

    case 'f':
    {
        if(findNode(root, character)==NULL)
            fprintf(fo, "Node %c not found\n", character);
        else fprintf(fo, "Node %c found\n", character);
    }
    break;

    case 't':
        switch(character)
        {
        case 'p':
        {
            preorder(root, fo);
            fprintf(fo,"\n");
        }
        break;

        case 'P':
        {
            postorder(root, fo);
            fprintf(fo,"\n");
        }
        break;

        case 'i':
        {
            inorder(root, fo);
            fprintf(fo,"\n");
        }
        break;
        }
        break;

    case 'g':
        switch(character)
        {
        case 'm':
        {
            bst_node *p=findMin(root);
            fprintf(fo, "The minimum key in the tree is %c\n",p->key);
        }
        break;

        case 'M':
        {
            bst_node *p=findMax(root);
            fprintf(fo, "The maximum key in the tree is %c\n",p->key);
        }
        break;
        }
        break;
    }
}

int main(int argc, char **argv)
{
    FILE *fi=fopen(argv[1],"r");
    FILE *fo=fopen(argv[2],"w");

    char operation[3];
    bst_node *root=createNode(' '); ///this will help me find the root of the tree

    while(fscanf(fi,"%s",&operation)!=EOF)
        commands(operation[0],operation[1],root,fo);

    fclose(fi);
    fclose(fo);
    return 0;
}
