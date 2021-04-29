#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_type
{
    char key;
    struct node_type *left;
    struct node_type *right;
}BSTNodeT;

BSTNodeT *createNode(char letter)
{
    BSTNodeT *p = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if(p)
    {
        p->key = letter;
        p->left = p->right = NULL;
    }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, char key)
{
    if(root == NULL)
        root = createNode(key);
    else
    {
        if(key < root->key)
            root->left = insertNode(root->left, key);
        else
            if(key > root->key)
                root->right = insertNode(root->right, key);
        else
            printf("\nNode with key = %c already exists\n", key);
    }
    return root;
}

BSTNodeT *find(BSTNodeT *root, char givenKey)
{
    if(root == NULL)
        return NULL;
    for(BSTNodeT *p = root; p != NULL;)
    {
        if(givenKey == p->key)
            return p;
        else
        {
            if(givenKey < p->key)
                p = p->left;
            else
                p = p->right;
        }
    }
    return NULL;
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

BSTNodeT *delNode(BSTNodeT *node, char key)
{
    if(node == NULL)
    {
        printf("Element not found");
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
        // found node
        if(node->right && node->left)
        {
            BSTNodeT *temp = findMin(node->right);
            node->key = temp->key;
            node->right = delNode(node->right, temp->key);
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

void preorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        preorder(p->left);
        preorder(p->right);
    }
}

void inorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        inorder(p->left);
        inorder(p->right);
    }
}

void postorder(BSTNodeT *p)
{
    if(p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
    }
}

BSTNodeT *root;

int main()
{
    FILE *in_file = fopen("data.in", "r");
    FILE *out_file = fopen("data.out", "w");
    char letter_1,letter_2;
    while(!feof(in_file))
    {
        fscanf(in_file, "%c %c", &letter_1, &letter_2);
        switch(letter_1)
        {
            case 'i':
                insertNode(root, letter_2);
                break;
            case 'd':
                delNode(find(root, letter_2), letter_2);
                break;
            case 'f':
                find(root, letter_2);
                break;
            case 't':
            {
                switch(letter_2)
                {
                    case 'p':
                        preorder(root);
                        break;
                    case 'P':
                        postorder(root);
                        break;
                    case 'i':
                        inorder(root);
                        break;
                    default:
                        fprintf(out_file, "Error");
                        break;
                }
                break;
            }
            case 'g':
            {
                switch(letter_2)
                {
                    case 'm':
                        findMin(root);
                        break;
                    case 'M':
                        findMax(root);
                        break;
                    default:
                        fprintf(out_file, "Error");
                        break;
                }
                break;
            }
            default:
                fprintf(out_file, "Error");
                break;
        }
    }
    fclose(in_file);
    fclose(out_file);
    return 0;
}
