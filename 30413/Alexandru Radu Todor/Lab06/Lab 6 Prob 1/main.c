#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[60];
    struct node *next, *prev;
}NodeT;

NodeT *insertNode(char name[], NodeT* root) { // this function inserts a new note at the beginning of the table
    NodeT *p = (NodeT *)malloc(sizeof(NodeT));
    if (p == NULL) { // if the new node couldn't be created, the function returns NULL
        return NULL;
    }
    strcpy(p->name, name);
    if (root != NULL) { // if the table is not empty, the old first note will have before it the new one
        root->prev = p;
    }
    p->next = root;
    p->prev = NULL;
    return p; // returning the new root
}

NodeT *find(char name[], NodeT* root) {
    while (root != NULL && strcmp(root->name, name) != 0){ // we search until we either found a node or checked everyone and didn't find anything
        root = root->next;
    }
    return root; // we returned the node that we found or NULL, if we didn't find a corresponding one
}

NodeT *delete(char name[], NodeT* root) {
    NodeT *p = find(name, root); // we check if the node we want to delete exists
    if (p == NULL) { // this is the case where it doesn't
        printf("%s not found in table to be deleted!\n", name);
    }
    else { // if it does exist
        if (p->next == NULL && p->prev == NULL) { // if the node we delete is the only one in the corresponding table, we empty the table
            root = NULL;
        }
        else if (p->prev == NULL) { // if it is the first in the table, the new root it's the next after it
            p->next->prev = NULL;
            root = p->next;
        }
        else if (p->next == NULL) { // if it's the last
            p->prev->next = NULL;
        }
        else { // if it's any other
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        printf("%s successfully deleted from table!\n", name);
    }
    free(p);
    return root;
}

void printTable(NodeT *nameTable[]) {
    int i;
    NodeT *p;
    printf("Hash table is:\n");
    for(i=0; i<4; i++) {
        p = nameTable[i];
        printf("nameTable[%d] = ", i);
        if (p == NULL) { // if the table is empty, print the message
            printf("empty");
        }
        while (p != NULL) { // if the table is not empty, print the contents
            printf("%s, ", p->name);
            p = p->next;
        }
        printf("\n");
    }
}

int generateHash(const char name[]) {
    // this function returns 4 values based on the name
    // 0, if both the first name's and last name's first letter are in the first half of the alphabet
    // 1, if the first name's first letter is in the second half of the alphabet and last name's is in the first half
    // 2, if the first name's first letter is in the first half of the alphabet and last name's is in the second half
    // 3, if both the first name's and last name's first letter are in the second half of the alphabet
    int i = 0, hash = 0;
    while (name[i] != ' ') {
        i++;
    }
    if (name[0] >= 'N') {
        hash = 1;
    }
    if (name[i + 1] >= 'N') {
        hash = hash + 2;
    }
    return hash;
}

int main(int argc, char* argv[]) {
    int i, hash;
    char command[61];
    NodeT *nameTable[4];

    for (i=0; i<4; i++) { // initialize the table with empty values
        nameTable[i] = NULL;
    }

    FILE* in = fopen(argv[1], "r"); // input file
    if (in == NULL) {
        printf("Input file not found or not introduced!");
        exit(0);
    }
    FILE* out = fopen(argv[2], "w"); // output file
    if (out == NULL) {
        printf("Output file not introduced!");
        exit(0);
    }

    while (fgets(command, sizeof(command), in) != NULL) { // checking each line of the file
        if (command[strlen(command) - 1] == '\n') { // in order not to get errors later, if the last element of the line is \n, we remove it from the string
            command[strlen(command) - 1] = 0;
        }
        if (command[1] >= 'A' && command[1] <= 'Z') { // we generate the hash only if there is a name
            hash = generateHash(command + 1);
        }
        switch (command[0]) {
            case 'i': // insert command
                nameTable[hash] = insertNode(command + 1, nameTable[hash]);
                break;
            case 'd': // delete command
                nameTable[hash] = delete(command + 1, nameTable[hash]);
                break;
            case 'f': // find command
                if (find(command + 1, nameTable[hash]) == NULL) {
                    printf("%s not found in table.\n", command + 1);
                }
                else {
                    printf("%s found at table index %d.\n", command + 1, hash);
                }
                break;
            case 'l': // print table command
                printTable(nameTable);
                break;
            default: // default case (errors)
                printf("Error! Command not found!\n");
                break;
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}
