#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node {
    char key;
    struct bst_node* left, * right;
} BSTNodeT;

BSTNodeT* createNode(char givenKey) {
    BSTNodeT* p = (BSTNodeT*)malloc(sizeof(BSTNodeT));
    if (p) {
        p->key = givenKey;
        p->left = p->right = NULL;
    }
    return p;
}

BSTNodeT* insertNode(BSTNodeT* root, char key, FILE* out) {
    if (root == NULL) {
        root = createNode(key);
        fprintf(out, "Node with key = %c was inserted in the tree.\n\n", key);
    }
    else {
        if (key < root->key) {
            root->left = insertNode(root->left, key, out);
        }
        else if (key > root->key) {
            root->right = insertNode(root->right, key, out);
        }
        else fprintf(out, "Node with key = %c already exists!\n\n", key);
    }
    return root;
}

BSTNodeT* find(BSTNodeT* root, char givenKey) {
    if (root == NULL) {
        return NULL;
    }
    for (BSTNodeT* p = root; p != NULL;) {
        if (givenKey == p->key) {
            return p;
        }
        else if (givenKey < p->key) {
            p = p->left;
        }
        else p = p->right;
    }
    return NULL;
}

void preorder(BSTNodeT* p, int level, FILE* out) {
    if (p != NULL) {
        for (int i = 0; i <= level; i++) {
            fprintf(out, " ");
        }
        fprintf(out, "%c\n", p->key);
        preorder(p->left, level + 1, out);
        preorder(p->right, level + 1, out);
    }
}

void inorder(BSTNodeT* p, int level, FILE* out) {
    if (p != NULL) {
        inorder(p->left, level + 1, out);
        for (int i = 0; i <= level; i++) {
            fprintf(out, " ");
        }
        fprintf(out, "%c\n", p->key);
        inorder(p->right, level + 1, out);
    }
}

void postorder(BSTNodeT* p, int level, FILE* out) {
    if (p != NULL) {
        postorder(p->left, level + 1, out);
        postorder(p->right, level + 1, out);
        for (int i = 0; i <= level; i++) {
            fprintf(out, " ");
        }
        fprintf(out, "%c\n", p->key);
    }
}

BSTNodeT* findMin(BSTNodeT* node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->left) {
        return findMin(node->left);
    }
    return node;
}

BSTNodeT* findMax(BSTNodeT* node) {
    if (node == NULL) {
        return NULL;
    }
    if (node->right) {
        return findMax(node->right);
    }
    return node;
}

BSTNodeT* delNode(BSTNodeT* node, char key, FILE* out) {
    if (node == NULL) {
        fprintf(out, "Element Not Found");
    }
    else if (key < node->key) {
        node->left = delNode(node->left, key, out);
    }
    else if (key > node->key) {
        node->right = delNode(node->right, key, out);
    }
    else {
        if (node->right && node->left) {
            BSTNodeT* temp = findMin(node->right);
            if (temp == NULL)
                return NULL;
            node->key = temp->key;
            node->right = delNode(node->right, temp->key, out);
        }
        else {
            BSTNodeT* temp = node;
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


int main(int argc, char* argv[]) {
    BSTNodeT* root = NULL;
    char command[3];

    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Input file not found or not introduced!");
        exit(0);
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Output file not introduced!");
        exit(0);
    }

    while (fscanf(in, "%s", command) != EOF) {
        switch (command[0]) {
            case 'i': // insert
                if (command[1] != 0) {
                    root = insertNode(root, command[1], out);
                }
                else fprintf(out, "Error! No node was typed!\n\n");
                break;
            case 'd': // delete
                if (command[1] != 0) {
                    if (delNode(root, command[1], out) == NULL) {
                        fprintf(out, "Node %c was not found to be deleted!\n\n", command[1]);
                    }
                    else fprintf(out, "Node %c was deleted!\n\n", command[1]);
                }
                else fprintf(out, "Error! No node was typed!\n\n");
                break;
            case 'f': // find
                if (command[1] != 0) {
                    if (find(root, command[1]) == NULL) {
                        fprintf(out, "Node %c was not found!\n\n", command[1]);
                    }
                    else fprintf(out, "Node %c was found!\n\n", command[1]);
                }
                else fprintf(out, "Error! No node was typed!\n\n");
                break;
            case 't': // traverse
                switch (command[1]) {
                    case 'p': // preorder
                        fprintf(out, "Preorder traverse:\n");
                        preorder(root, 0, out);
                        fprintf(out, "\n");
                        break;
                    case 'i': // inorder
                        fprintf(out, "Inorder traverse:\n");
                        inorder(root, 0, out);
                        fprintf(out, "\n");
                        break;
                    case 'P': // postorder
                        fprintf(out, "Postorder traverse:\n");
                        postorder(root, 0, out);
                        fprintf(out, "\n");
                        break;
                    default:
                        fprintf(out, "Nonexistent traversal!\n\n");
                }
                break;
            case 'g': // get
                switch (command[1]) {
                    case 'm': // minimum
                        fprintf(out, "The minimum node from the tree is %c.\n\n", findMin(root)->key);
                        break;
                    case 'M': // maximum
                        fprintf(out, "The maximum node from the tree is %c.\n\n", findMax(root)->key);
                        break;
                    default:
                        fprintf(out, "Get command incomplete or wrong!\n\n");
                }
                break;
            default:
                fprintf(out, "Error! Command not found!\n\n");
        }
    }
    fclose(in);
    fclose(out);
    printf("Success!");
    return 0;
}
