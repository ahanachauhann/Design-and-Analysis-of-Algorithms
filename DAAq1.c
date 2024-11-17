#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

typedef struct Node Node;

struct BST {
    Node* root;
};

typedef struct BST BST;
Node* insert_recursive(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key) root->left = insert_recursive(root->left, key);
    else root->right = insert_recursive(root->right, key);
    return root;
}
void insert_iterative(BST* bst, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;

    if (bst->root == NULL) {
        bst->root = newNode;
        return;
    }

    Node* current = bst->root;
    while (1) {
        if (key < current->key) {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            }
            current = current->right;
        }
    }
}
double test_recursive_insertion(BST* bst, int* elements, int n) {
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        bst->root = insert_recursive(bst->root, elements[i]);
    }
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double test_iterative_insertion(BST* bst, int* elements, int n) {
    clock_t start = clock();
    for (int i = 0; i < n; i++) {
        insert_iterative(bst, elements[i]);
    }
    return (double)(clock() - start) / CLOCKS_PER_SEC; }
void generate_random_elements(int* elements, int n) {
    for (int i = 0; i < n; i++) {
        elements[i] = rand() % (n * 2);
    }
}

int main() {
    int n = 1000;
    int elements[n];
    generate_random_elements(elements, n);

    BST bst_recursive = {NULL};
    BST bst_iterative = {NULL};

    double time_recursive = test_recursive_insertion(&bst_recursive, elements, n);
    double time_iterative = test_iterative_insertion(&bst_iterative, elements, n);

    printf("Recursive Insertion Time: %.6f seconds\n", time_recursive);
    printf("Iterative Insertion Time: %.6f seconds\n", time_iterative);

    return 0;
}
