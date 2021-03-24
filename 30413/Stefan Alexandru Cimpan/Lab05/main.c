#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct node_type
{
    char key;
    struct node_type *left, *right;
} NodeT;

void error(const char *msg)
{
    printf(msg);
    exit(1);
}
NodeT *createNode(char key)
{
    NodeT *temp = (NodeT*)calloc(1,sizeof(NodeT));
    if(temp)
    {
        temp->key = key;
        temp->left = temp->right = NULL;
    }
    else
        error("No space\n");
    return temp;
}


NodeT *insertNode(NodeT *root, char key)
{
    if(root == NULL)
    {
        root = createNode(key);
        return root;
    }
    else
    {
        if(key < root->key)/// left
            root->left = insertNode(root->left, key);
        else if (key > root->key)/// right
            root->right = insertNode(root->right, key);
        else
            printf("\nnode wt. key: %c is already in the tree!\n", key);
    }
    return root;
}

NodeT *findNode(NodeT *root, char key)
{
    if(root == NULL)
        return NULL;
    for(NodeT *q = root; q != NULL;)
    {
        if(q->key == key)
            return q;
        else if(key < q->key)
            q = q->left;
        else q = q->right;
    }
    return NULL;
}

NodeT *findMin(NodeT *p)
{
    if(p == NULL)
        return NULL;
    if(p->left)
        return findMin(p->left);
    else
        return p;
}

NodeT *findMax(NodeT *p)
{
    if(p == NULL)
        return NULL;
    if(p->right)
        return findMax(p->right);
    else
        return p;
}

NodeT *deleteNode(NodeT *root, char key)
{
    if(root == NULL)
        printf("\nElement not foun!\n");

    if(key < root->key)
        root->left = deleteNode(root->left, key);

    else if(key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if(root->left && root->right)
        {

            NodeT *temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        else
        {
            NodeT *temp = root;
            if(root->left == NULL)
                root = root->right;
            else if(root->right == NULL)
                root = root->left;
            free(temp);/// del
        }
    }
    return root;
}

void deleteTree(NodeT *root)
{
    if(root != NULL)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

void preorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%c\n", root->key);
        preorder(out, root->left, level + 1);
        preorder(out, root->right, level + 1);
    }

}

void inorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        inorder(out, root->left, level + 1);
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%c\n", root->key);
        inorder(out, root->right, level + 1);
    }
}

void postorder(FILE *out, NodeT *root, int level)
{
    int i;
    if(root != NULL)
    {
        postorder(out, root->left, level + 1);
        postorder(out, root->right, level + 1);
        for(i = 0; i<= level; i++)  fprintf(out, "  ");
        fprintf(out, "%c\n", root->key);
    }
}

void processInput(FILE *in, FILE *out, NodeT *root)
{
    char command[3];

    while(fscanf(in, "%s", command) != EOF)
    {
        NodeT *temp;
        switch(command[0])
        {
        case 'i':
            insertNode(root, command[1]);
            break;
        case 'd':
            deleteNode(root, command[1]);
            fprintf(out, "\nNode %c was deleted.\n", command[1]);
            break;
        case 'f':
            temp = findNode(root, command[1]);
            if(temp)
                fprintf(out, "The searched node is: %c\n", temp->key);
            break;
        case 't':
            if(command[1] == 'p')
            {
                fprintf(out, "\nPreorder:\n");
                preorder(out, root, 0);
                fprintf(out, "\n");
            }
            else if (command[1] == 'P')
            {
                fprintf(out, "\nPostorder:\n");
                postorder(out, root, 0);
                fprintf(out, "\n");
            }
            else if (command[1] == 'i')
            {
                fprintf(out, "\nInorder:\n");
                inorder(out, root, 0);
                fprintf(out, "\n");
            }
            break;
        case 'g':
            if(command[1] == 'm')
            {
                temp = findMin(root);
                if(temp)
                    fprintf(out, "Min node is: %c\n", temp->key);
            }
            else if (command[1] == 'M')
            {
                temp = findMax(root);
                if(temp)
                    fprintf(out, "Max node is: %c\n", temp->key);
            }
            break;
        };
    }
    printf("Done processing input file!");
}

int main(int argc, char **argv)
{
    FILE *in,*out;//decl fisiere
    NodeT *root = NULL;
    processInput(in, out, root);
    fclose(in);
    fclose(out);
    deleteTree(root);//free mem
    return 0;
}
