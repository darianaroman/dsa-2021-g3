#include <stdio.h>
#include <stdlib.h>

int countLines(FILE *filePtr)
{
    int count = 0;
    char c;
    while(c != EOF) {
        c = fgetc(filePtr);
        if (c == '\n') {
            count++;
        }
    }
    count++;
    rewind(filePtr);
    return count;
}

typedef struct node_type
{
    char key;
    struct node_type *left, *right;
} NodeT;

NodeT *createNode(char key)
{
    NodeT *p = (NodeT*) malloc (sizeof(NodeT));
    if(p) {
        p->key = key;
        p->left = p->right = NULL;
    }
    return p;
}

NodeT *insertLetter(NodeT *root, char letter, FILE *fileO)
{
    if (root == NULL) {
        root = createNode(letter);
    }
    else {
        if (letter < root->key) {
            root->left = insertLetter(root->left, letter, fileO);
        }
        else if (letter > root->key) {
            root->right = insertLetter(root->right, letter, fileO);
        }
        else {
            fprintf(fileO, "letter %c already in the tree", letter);
        }
    }
    return root;
}

NodeT *findNode(NodeT *root, char letter)
{
    if (root == NULL) {
        return NULL;            ///empty BST
    }
    for (NodeT *p = root; p != NULL;) {
        if (letter == p->key) {
            return p;
        }
        else {
            if (letter < p->key) {
                p = p->left;
            }
            else {
                p = p->right;
            }
        }
    }
    return NULL;
}

NodeT *findMax (NodeT *node)
{
    if (node == NULL) {
        return NULL;            /// empty tree
    }
    if (node->right) {
        return findMax(node->right);
    }
    else {
        return node;
    }
}

NodeT *findMin (NodeT *node)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->left) {
        return findMin(node->left);
    }
    else {
        return node;
    }
}

NodeT *deleteLetter(NodeT *node, char letter)
{
    if (node == NULL) {
        printf("element not found");
    }
    else if (letter < node->key) {
        node->left = deleteLetter(node->left, letter);
    }
    else if (letter > node->key) {
        node->right = deleteLetter(node->right, letter);
    }
    else {
        if (node->right && node->left) {
            NodeT *temp = findMin(node->right);
            node->key = temp->key;
            node->right = deleteLetter(node->right, temp->key);
        }
        else {
            NodeT *temp = node;
            if (node->left == NULL) {
                node = node->right;
            }
            else if (node->right == NULL) {
                node = node->left;
            }
            free(temp);
        }
    }
    return node;
}

void traversalPre(NodeT *p, int level, FILE *fileO)
{
    if (p != NULL) {
        for(int i = 0; i <= level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%c\n", p->key);

        traversalPre(p->left, level + 1, fileO);
        traversalPre(p->right, level + 1, fileO);
    }
}

void traversalIn(NodeT *p, int level, FILE *fileO)
{
        if (p != NULL) {
        traversalIn(p->left, level + 1, fileO);

        for(int i = 0; i < level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%c\n", p->key);

        traversalIn(p->right, level + 1, fileO);
    }
}

void traversalPost(NodeT *p, int level, FILE *fileO)
{
    if (p != NULL) {
        traversalPost(p->left, level + 1, fileO);
        traversalPost(p->right, level + 1, fileO);

        for(int i = 0; i < level; i++) {
            fprintf(fileO, "  ");
        }
        fprintf(fileO, "%c\n", p->key);
    }
}

int main(int argc, char *argv[])
{
    FILE *fileI = fopen(argv[1], "r");
    FILE *fileO = fopen(argv[2], "w");

    int numberLines = countLines(fileI);
    int i;
    char command;
    char letter;

    NodeT *root = NULL;
    NodeT *aux = NULL;

    for (i = 0; i < numberLines; i++) {
        command = fgetc(fileI);
        letter = fgetc(fileI);
        fgetc(fileI);           /// to pass the end line
        fprintf(fileO, "%c : ", command);

        switch(command) {

        case 'i' :
            root = insertLetter(root, letter, fileO);
            fprintf(fileO, "inserted node with key = %c\n", letter);
            break;

        case 'd' :
            root = deleteLetter(root, letter);
            fprintf(fileO, "deleted node with key = %c\n", letter);
            break;

        case 'f' :
            aux = findNode(root, letter);
            if(aux == NULL) {
                fprintf(fileO, "the tree doesn't contain node with key = %c", letter);
            }
            else {
                fprintf(fileO, "found node with key = %c\n", aux->key);
            }
            break;

        case 't' :
            switch(letter) {

            case 'p' :
                fprintf(fileO, "tree preorder:\n");
                traversalPre(root, 0, fileO);
                fprintf(fileO, "\n");
                break;

            case 'i' :
                fprintf(fileO, "tree inorder:\n");
                traversalIn(root, 0, fileO);
                fprintf(fileO, "\n");
                break;

            case 'P' :
                fprintf(fileO, "tree postorder:\n");
                traversalPost(root, 0, fileO);
                fprintf(fileO, "\n");
                break;

            default :
                fprintf(fileO, "error! command unknown");
            }
            break;

        {
        case 'g' :
            switch(letter) {

            case 'M' :
                fprintf(fileO, "maximum is: %c\n", findMax(root)->key);
                break;

            case 'm' :
                fprintf(fileO, "minimum is: %c\n", findMin(root)->key);
                break;

            default :
                fprintf(fileO, "error! command unknown");
            }
            break;
        }

        default :
            fprintf(fileO, "error! command unknown");
        }
    }

    return 0;
}
