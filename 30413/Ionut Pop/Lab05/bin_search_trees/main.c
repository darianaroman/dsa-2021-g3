#include <stdio.h>
#include <stdlib.h>

typedef struct node_type{
  char key;
  struct node_type *left, *right;
} BSTNodeT;

BSTNodeT *createNode(char givenKey){
    BSTNodeT *p = (BSTNodeT *) malloc (sizeof (BSTNodeT));
    if (p){
        p->key = givenKey;
        p->left = p-> right = NULL;
        }
    return p;
}

BSTNodeT *insertNode(BSTNodeT *root, int key){
    if (root == NULL)
        root = createNode(key);
    else{
        if (key < root->key)
            root->left = insertNode(root->left, key);
        else if (key > root->key)
            root->right = insertNode(root ->right, key);
        else
            printf("\nNode with key = %d already exists\n", key);
        }
    return root;
}

BSTNodeT *find(BSTNodeT *root, char givenKey){
  if (root == NULL) return NULL;
  for (BSTNodeT *p = root; p != NULL;)
  {
    if (givenKey == p->key) return p;
    else
    if (givenKey < p->key) p = p->left;
    else                   p = p->right;
  }
  return NULL;
}

BSTNodeT *findMin(BSTNodeT *node){
    if(node == NULL)
        return NULL;
    if(node->left)
        return findMin(node->left);
    else
        return node;
}

BSTNodeT *findMax(BSTNodeT *node){
    if(node == NULL)
        return NULL;
    if(node->right)
        return findMax(node->right);
    else
        return node;
}

BSTNodeT* delNode(BSTNodeT* node, char key)
{
    if(node == NULL)
        printf("Element Not Found");
    else if(key < node->key)
        node->left = delNode(node->left, key);
    else if(key > node->key)
        node->right = delNode(node->right, key);
    else{
        if(node->right && node->left){
            BSTNodeT *temp = findMin(node->right);
            node -> key = temp->key;
            node -> right = delNode(node->right, temp->key);
            }
        else{
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

void delTree(BSTNodeT *root){
  if (root != NULL){
    delTree(root ->left);
    delTree(root ->right);
    free(root);
    }
}

void preorder(FILE *out, BSTNodeT *p){
  if (p != NULL){
    fprintf(out, "%c ", p->key);
    preorder(out, p->left);
    preorder(out, p->right);
  }
}

void inorder(FILE *out, BSTNodeT *p){
  if (p != NULL){
    inorder(out, p->left);
    fprintf(out, "%c ", p->key);
    inorder(out, p->right);
  }
}

void postorder(FILE *out, BSTNodeT *p){
  if (p != NULL){
    postorder(out, p->left);
    postorder(out, p->right);
    fprintf(out, "%c ", p->key);
  }
}

int main(int argc, char *arcv[])
{
    FILE *in=fopen("./input", "r");
    FILE *out=fopen("./output", "w");
    //FILE *in=fopen(arcv[1], "r");
    //FILE *out=fopen(arcv[2], "w");

    BSTNodeT *root;
    char command, key;
    root=NULL;

    do {
        char *word=(char *)malloc(3*sizeof(char));
        fscanf(in, "%s ", word);
        command=word[0];
        key=word[1];

        if (command=='i'){
        root=insertNode(root, key);
        }
        else if(command=='d')
            root=delNode(root, key);
        else if(command=='f'){
            if (find(root, key)!=NULL)
                fprintf(out, "node %c is in tree\n", key);
            else
                fprintf(out, "node %c not found\n", key);
            }
        else if (command=='t'){
            if (key=='p')
                preorder(out, root);
            else if (key=='P')
                postorder(out, root);
            else if (key=='i')
                inorder(out, root);
            else
                fprintf(out, "\n%c is not a valid traversal command", key);
        fprintf(out, "\n");
        }
        else if(command=='g'){
            if (key=='m'){
                BSTNodeT *min_node=findMin(root);
                fprintf(out, "minimum node is: %c", min_node->key);
                }
            else if(key=='M'){
                BSTNodeT *max_node=findMax(root);
                fprintf(out, "maximum node is: %c", max_node->key);
                }
            else
                fprintf(out, "\n%c is not a valid command", key);
            fprintf(out, "\n");
        }
        else
            fprintf(out, "\ncommand %c is not valid\n", command);

        free(word);
    } while (!feof(in));



    return 0;
}
