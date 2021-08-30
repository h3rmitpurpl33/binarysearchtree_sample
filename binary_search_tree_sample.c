#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *add_node(node *p, int key);

void show_inorder(node *p);

void delete_tree(node *p);

int main() {
    int sel, key;
    node *root;
    root = NULL;
    while (1) {
        printf("\nMenu selections\n");
        printf("----------\n");
        printf("1. Add Node\n");
        printf("2. Show Tree\n");
        printf("3. Exit\n");

        printf("enter choice :  ");
        scanf("%d", &sel);

        switch (sel) {
            case 1:
                printf("key: ");
                scanf("%d", &key);
                root = add_node(root, key);
                break;

            case 2:
                printf("\nDeleted keys: ");
                delete_tree(root);
                return 0;

            default:
                printf("\nWrong choice\n");
                break;
        }
    }
    return 0;
}

node *add_node(node *p, int key) {
    if (p == NULL) {
        p = (node *) malloc(sizeof(node));
        if (p == NULL) {
            printf("error: not available memory\n");
            exit(EXIT_FAILURE);
        }
        p->left = p->right = NULL;
        p->key = key;
    } else {
        if (key < p->key) {
            p->left = add_node(p->left, key);
        } else if (key > p->key) {
            p->right = add_node(p->right, key);
        } else {
            printf("error: key(%d) exists\n", key);
        }
    }
    return p;
}

void show_inorder(node *p) {
    if (p == NULL) {
        return;
    }
    show_inorder(p->left);
    printf("%d", p->key);
    show_inorder(p->right);
}

void delete_tree(node *p) {
    if (p == NULL) {
        return;
    }
    delete_tree(p->left);
    delete_tree(p->right);
    printf("%d ", p->key);
    free(p);
}
