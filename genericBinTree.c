#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "genericBinTree.h"

typedef struct BinTree {
    Ptr val;
    struct BinTree* left;
    struct BinTree* right;
    BinTreeFunctions funcs;
} BinTree;

static int isEmpty(BinTree* root) {
    if (root == NULL) {
        return 1;
    }
    if (root->val == NULL) {
        return 1;
    }
    return 0;
}

BinTree* create_bin_tree(BinTreeFunctions funcs) {
    BinTree* root = malloc(sizeof(BinTree));
    if (root == NULL) {
        return NULL;
    }
    root->funcs = funcs;
    root->val = NULL;
    root->left = NULL;
    root->right = NULL;
    return root;
}

BinTree* find_in_bin_tree(BinTree* root, Ptr val) {
    if (isEmpty(root)) {
        return NULL;
    }
    if (root->funcs.compare(root->val, val) > 0) {
        return find_in_bin_tree(root->left, val);
    }
    if (root->funcs.compare(root->val, val) < 0) {
        return find_in_bin_tree(root->right, val);
    }
    return root;
}

int size_of_bin_tree(BinTree* root) {
    if (isEmpty(root)) {
        return 0;
    }
    return 1 + size_of_bin_tree(root->left) + size_of_bin_tree(root->right);
}

void destroy_bin_tree(BinTree* root) {
    if (root == NULL) {
        return;
    }
    destroy_bin_tree(root->left);
    destroy_bin_tree(root->right);
    root->funcs.destroy(root->val);
    free(root);
}

Result add_to_bin_tree(BinTree* root, Ptr val) {
    if (root == NULL) {
        return FAILURE;
    }
    if (root->val == NULL) {
        root->val = root->funcs.allocate();
        if (root->val == NULL) {
            return MEM_ERROR;
        }
        root->funcs.copy(root->val, val);
        return SUCEESS;
    }
    if (root->funcs.compare(root->val, val) > 0) {
        if (root->left != NULL) {
            return add_to_bin_tree(root->left, val);
        }
        root->left = create_bin_tree(root->funcs);
        if (root->left == NULL) {
            return MEM_ERROR;
        } else {
            root->left->val = root->funcs.allocate();
            if (root->left->val == NULL) {
                destroy_bin_tree(root->left);
                return MEM_ERROR;
            }
            root->funcs.copy(root->left->val, val);
            return SUCEESS;
        }
    }
    if (root->funcs.compare(root->val, val) < 0) {
        if (root->right != NULL) {
            return add_to_bin_tree(root->right, val);
        }
        root->right = create_bin_tree(root->funcs);
        if (root->right == NULL) {
            return MEM_ERROR;
        } else {
            root->right->val = root->funcs.allocate();
            if (root->right->val == NULL) {
                destroy_bin_tree(root->right);
                return MEM_ERROR;
            }
            root->funcs.copy(root->right->val, val);
            return SUCEESS;
        }
    }
    return FAILURE;
}

BinTree* create_bin_tree_from_arr(BinTreeFunctions funcs, Ptr arr[], int size) {
    if (size == 0) {
        return NULL;
    }
    BinTree* root = create_bin_tree(funcs);
    if (root == NULL) {
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        Result result = add_to_bin_tree(root, arr[i]);
        if (result != SUCEESS) {
            destroy_bin_tree(root);
            return NULL;
        }
    }
    return root;
}

static int arr_from_tree_pre_order(BinTree* root, Ptr arr[], int size, int last);
static Result remove_from_arr(BinTreeFunctions funcs, Ptr arr[], int size, Ptr val);

Result remove_from_bin_tree(BinTree** rootPtr, Ptr val) {
    assert(rootPtr != NULL);
    BinTree* root = *rootPtr;
    if (!find_in_bin_tree(root, val)) {
        return FAILURE;
    }
    int size = size_of_bin_tree(root);
    Ptr* arr = malloc(size * sizeof(Ptr));
    if (arr == NULL) {
        return MEM_ERROR;
    }
    int last = arr_from_tree_pre_order(root, arr, size, -1);
    assert(last == size - 1);

    Result result = remove_from_arr(root->funcs, arr, size, val);
    assert(result == SUCEESS);

    BinTree* new_root = create_bin_tree_from_arr(root->funcs, arr, size-1);
    for (int i = 0; i < size-1; i++) {
        root->funcs.destroy(arr[i]);
    }
    free(arr);

    if (new_root == NULL) {
        return MEM_ERROR;
    }

    destroy_bin_tree(*rootPtr);
    *rootPtr = new_root;
    return SUCEESS;
}

void print_pre_order(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    root->funcs.print(root->val);
    print_pre_order(root->left);
    print_pre_order(root->right);
}

void print_in_order(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    print_in_order(root->left);
    root->funcs.print(root->val);
    print_in_order(root->right);
}

void print_post_order(BinTree* root) {
    if (isEmpty(root)) {
        return;
    }
    print_post_order(root->left);
    print_post_order(root->right);
    root->funcs.print(root->val);
}

static int arr_from_tree_pre_order(BinTree* root, Ptr arr[], int size, int last) {
    if (root == NULL) {
        return last;
    }
    int i = last + 1;
    assert(i < size);
    arr[i] = root->funcs.allocate();
    root->funcs.copy(arr[i], root->val);
    last = arr_from_tree_pre_order(root->left, arr, size, i);
    return arr_from_tree_pre_order(root->right, arr, size, last);
}

static Result remove_from_arr(BinTreeFunctions funcs, Ptr arr[], int size, Ptr val) {
    int val_idx = -1;
    for (int i = 0; i < size; i++) {
        if (funcs.compare(arr[i], val) == 0) {
            val_idx = i;
            break;
        }
    }
    if (val_idx == -1) {
        return FAILURE;
    }
    funcs.destroy(arr[val_idx]);
    for (int i = val_idx; i < size - 1; i++) {
        arr[i] = arr[i+1];
    }
    arr[size-1] = NULL;
    return SUCEESS;
}

Ptr get_value_in_root(BinTree* root) {
    if (root == NULL) {
        NULL;
    }
    return root->val;
}
