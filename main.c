#include <stdio.h>
#include <stdlib.h>


struct tree {
    int value;
    struct tree * left;
    struct tree * right;
};

struct tree * create(int value){
    struct tree * root = malloc(sizeof(struct tree));
    root->left = NULL;
    root->right = NULL;
    root->value = value;
    return root;
}

void insert(struct tree * root, int value){
    if(root == NULL){
        return;
    }
    if(value < root->value){
        if(root->left != NULL) {
            insert(root->left, value);
            return;
        }
        root->left = create(value);
        return;
    }
    if(root->right != NULL) {
        insert(root->right, value);
        return;
    }
    root->right = create(value);
    return;
}

void myprint(struct tree * root){
    if(root != NULL) {
        myprint(root->left);
        printf(" %d ", root->value);
        myprint((root->right));
    }
}
int findMin(struct tree * root, struct tree * parent){

    if(root->left == NULL){
        int tmp = root->value;
        if(parent->left == root){
            parent->left = root->right;
            free(root);
            return tmp;
        }
        parent->right = root->right;
        free(root);
        return tmp;
    }
    return findMin(root->left, root);
}

void myremove(int value, struct tree * root, struct tree * parent){
    if(root == NULL){
        return;
    }
    if(root->value == value){
        if(root->right != NULL){
            root->value = findMin(root->right, root);
            return;
        }
        if(root->left != NULL){
            root->value = root->left->value;
            root->right = root->left->right;
            struct tree * tmp = root->left->left;
            free(root->left);
            root->left = tmp;
            return;
        }
        if(parent->left == root){
            parent->left = NULL;
            free(root);
            return;
        }
        parent->right = NULL;
        free(root);
        return;
    }
    if(value < root->value){
        myremove(value, root->left, root);
        return;
    }
    myremove(value, root->right, root);
    return;

}

int main() {
    struct tree * tree;
    tree = create(44);
    int tab[10] = {7, 19, 90, 790, 69, 30, 12, 43, 59, 1};
    for (int i = 0; i < 10; ++i) {
        insert(tree, tab[i]);
    }
    myprint(tree);
    myremove(19, tree, tree);
    printf("\n");
    myprint(tree);
    printf("\n");
    myremove(1, tree, tree);
    printf("\n");
    myprint(tree);
    myremove(790, tree, tree);
    printf("\n");
    myprint(tree);
    myremove(44, tree, tree);
    printf("\n");
    myprint(tree);
    myremove(59, tree, tree);
    printf("\n");
    myprint(tree);
    return 0;
}