#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *add_node(node *p, int key);

void show_tree(node *p);

void delete_tree(node *p);

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
        printf("2. Show Tree\n");
        printf("3. Find Node\n");
        printf("4. Show preorder\n");
        printf("5. Show postorder\n");
        printf("6. Exit\n");

        printf("enter choice :  ");
        scanf("%d", &sel);

        switch (sel) {
            case 1:
                printf("enter key: ");
                scanf("%d", &key);
                root = add_node(root, key);
                break;

            case 2:
                show_tree(root);
                break;

            case 3:
                printf("enter key to search : ");
                scanf("%d", &key);
                root = find_node(root, key);
                printf("key %d found\n", root->key);
                break;
            case 4:
                show_preorder(root);
                break;
            case 5:
                show_postorder(root);
                break;
            case 6:
                exit(0);
            default:
                printf("\nwrong key\n");
                break;


        }
    }
    return 0;
}

node *add_node(node *p, int key) {
    if (p == NULL) {
        p = (node *) malloc(sizeof(node));
        if (p == NULL) {
            printf("not available memory\n");
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
            printf("key %d already exists ", key);
        }
    }
    return p;
}

void show_tree(node *p) {
    if (p == NULL) {
        return;
    }
    show_tree(p->left);
    printf("%d ", p->key);
    show_tree(p->right);
}

void delete_tree(node *p) {
    if (p == NULL) {
        return;
    }
    delete_tree(p->left);
    delete_tree(p->right);
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
    show_postorder(p->left);
    show_postorder(p->right);
    printf("%d ", p->key);
}
