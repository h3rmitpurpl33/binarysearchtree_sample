#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *add_node(node *p, int key);

void show_tree(node *p);

void delete_node(node *p);

node *find_node(node *p, int key);

void show_preorder(node *p);

void show_postorder(node *p);

int main() {
    int sel, key;
    node *root;
    root = NULL;
    while (1) {
        printf("\nMenu selections\n");
        printf("----------\n");
        printf("1. Add Node\n");
        printf("2. Show In Order\n");
        printf("3. Show Tree\n");
        printf("3. Find Node\n");
        printf("4. Show preorder\n");
        printf("5. Show postorder\n");
        printf("6. Exit\n");

        printf("enter choice :  ");
        scanf("%d", &sel);

        switch (sel) {
            case 1:
                printf("enter key : ");
                scanf("%d", &key);
                root = add_node(root, key);
                break;
            case 2:
                if (root == NULL) {
                    printf("empty list\n");
                } else {
                    show_tree(root);
                }
                break;
            case 3:
                printf("deleted keys\n");
                delete_node(root);
                return 0;
            case 4:
                printf("enter key to search : ");
                scanf("%d", &key);
                root = find_node(root, key);
                if (root == NULL) {
                    printf("key not found\n");
                } else {
                    printf("found key %d", root->key);
                }
                break;
            case 5:
                if (root == NULL) {
                    printf("empty list\n");
                } else {
                    show_preorder(root);
                }
                break;
            case 6:
                if (root == NULL) {
                    printf("empty list\n");
                } else {
                    show_postorder(root);
                }
                break;
            default:
                printf("wrong key\n");
                break;
        }
    }
    return 0;
}

node *add_node(node *p, int key) {
    if (p == NULL) {
        p = malloc(sizeof(node));
        if (p == NULL) {
            printf("not available memory\n");
            exit(EXIT_FAILURE);
        }
        p->left = p->right = NULL;
        p->key = key;
        if (key < p->key) {
            p->left = add_node(p->left, key);
        } else if (key > p->key) {
            p->right = add_node(p->right, key);
        } else {
            printf("key %d already exists ", key);
        }
    }
    return NULL;
}

void show_tree(node *p) {
    if (p == NULL) {
        return;
    }
    show_tree(p->left);
    printf("%d", p->key);
    show_tree(p->right);
}

void delete_node(node *p) {
    if (p == NULL) {
        return;
    }
    delete_node(p->left);
    delete_node(p->right);
    free(p);
}

node *find_node(node *p, int key) {
    if (p == NULL) {
        return NULL;
    }
    while (p != NULL) {
        if (key < p->key) {
            p = p->left;
        } else if (key > p->key) {
            p = p->right;
        } else {
            return p;
        }
    }
    return NULL;
}

void show_preorder(node *p) {
    if (p == NULL) {
        return;
    }
    printf("%d ", p->key);
    show_preorder(p->left);
    show_preorder(p->right);
}

void show_postorder(node *p) {
    if (p == NULL) {
        return;
    }
    show_preorder(p->left);
    show_preorder(p->right);
    printf("%d ", p->key);
}
