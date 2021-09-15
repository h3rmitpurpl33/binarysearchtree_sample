#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree_node {
    int data;
    struct tree_node *left;
    struct tree_node *right;
};

struct btree {
    struct tree_node *root;
};

struct btree *create_btree();

struct tree_node *new_tree_node(int num);

struct tree_node *find_tree_node(struct btree *bt, int key);

bool insert_in_btree(struct btree *bt, int num);

void display_btree(struct btree *bt);

void display_btree_rec(struct tree_node *cn);

bool remove_from_tree(struct btree *bt, int key);

struct tree_node *find_left_most(struct tree_node *rt);

struct tree_node *find_right_most(struct tree_node *rt);


int main() {
    char ch;
    int timi;

    struct btree *mytree = create_btree();
    struct tree_node *node_ptr;

    while (1) {
        printf("0.Exit, 1.Insert, 2.Find Node, 3.Delete, 4.Show Tree\n");
        ch = getchar();
        switch (ch) {
            case '0':
                exit(0);
            case '1':
                printf("timh : ");
                scanf("%d", &timi);
                if (insert_in_btree(mytree, timi) == false) {
                    puts("den yparxei diathesimh mnhmh\n");
                }
                break;
            case '2':
                printf("timh : ");
                scanf("%d", &timi);
                node_ptr = find_tree_node(mytree, timi);
                if (node_ptr != NULL) {
                    printf("vrethike\n");
                } else {
                    printf("den vrethike\n");
                }
                break;
            case '3':
                printf("timh : ");
                scanf("%d", &timi);
                if (!remove_from_tree(mytree, timi))
                    printf("komvos me kleidi %d den yparxei", timi);
                break;
            case '4':
                display_btree(mytree);
                printf("\n");
                break;
            default:
                puts("lathos plhktro\n");
                break;

        }
    }
    return 0;
}


struct btree *create_btree() {
    struct btree *btr = (struct btree *) malloc(sizeof(struct btree));
    btr->root = NULL;
    return btr;
}

struct tree_node *new_tree_node(int num) {
    struct tree_node *new;
    new = malloc(sizeof(struct tree_node));
    if (new == NULL) {
        return new;
    }
    new->data = num;
    new->left = NULL;
    new->right = NULL;
    return new;
}

void display_btree_rec(struct tree_node *cn) {
    if (cn == NULL) {
        return;
    }
    display_btree_rec(cn->left);
    printf("%d ", cn->data);
    display_btree_rec(cn->right);
}

void display_btree(struct btree *bt) {
    if (bt->root == NULL) {
        return;
    }
    display_btree_rec(bt->root);
}

struct tree_node *find_in_btree(struct btree *bt, int key) {
    struct tree_node *current;
    current = bt->root;
    while (current->data != key) {
        if (key < current->data)
            current = current->left;
        else {
            current = current->right;
        }
        if (current == NULL) {
            return NULL;
        }
    }
    return current;
}

bool insert_in_btree(struct btree *bt, int num) {
    struct tree_node *next, *current, *ptr;
    bool isleft;
    next = current = bt->root;
    ptr = new_tree_node(num);
    if (ptr == NULL) {
        return false;
    }
    if (bt->root == NULL) {
        bt->root = ptr;
        return true;
    }
    while (1) {
        if (num < current->data) {
            next = current->left;
            isleft = true;
        } else {
            next = current->right;
            isleft = false;
        }
        if (next == NULL) {
            if (isleft)
                current->left = ptr;
            else
                current->right = ptr;
            return true;
        }
        current = next;
    }
}

bool remove_from_tree(struct btree *bt, int key) {
    struct tree_node *current;
    struct tree_node *parent;
    bool isLeftChild = true;
    current = parent = bt->root;
    while (current->data != key) {
        parent = current;
        if (key < current->data) {
            isLeftChild = true;
            current = current->left;
        } else {
            isLeftChild = false;
            current = current->right;
        }
        if (current == NULL) {
            return false;
        }
    }
    if (current->left == NULL && current->right == NULL) {
        if (current == bt->root)
            bt->root = NULL;
        else if (isLeftChild)
            parent->left = NULL;
        else
            parent->right = NULL;
    } else if (current->right == NULL) {
        if (current == bt->root)
            bt->root = current->left;
        else if (isLeftChild)
            parent->left = current->left;
        else
            parent->right = current->left;
    } else if (current->left == NULL)
        if (current == bt->root)
            bt->root = current->right;
        else if (isLeftChild)
            parent->left = current->right;
        else
            parent->right = current->right;
    else {
        struct tree_node *successor, *temp, *old_root;
        if (current == bt->root) {
            temp = bt->root->left;
            successor = find_left_most(bt->root->right);
            bt->root = bt->root->right;
            successor->left = temp;
        } else if (isLeftChild) {
            successor = find_left_most(current->right);
            successor->left = current->left;
            parent->left = current->right;
        } else {
            successor = find_right_most(current->left);
            successor->right = current->right;
            parent->right = current->left;
        }

    }
    free(current);
    return true;
}

struct tree_node *find_left_most(struct tree_node *rt) {
    struct tree_node *current;
    if (rt == NULL) {
        return NULL;
    }
    current = rt;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct tree_node *find_right_most(struct tree_node *rt) {
    struct tree_node *current;
    if (rt == NULL) {
        return NULL;
    }
    current = rt;
    while (current->right != NULL)
        current = current->right;
    return current;
}

