// Tree Traversal Starter Code
#include <stdlib.h>
#include <stdio.h>

struct node
{
    node *left, *right;
    int data;
};

node *createNode(int data)
{
    node *n = (node *)malloc(sizeof(node));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

node *createHardCodedTree()
{
    node *root = createNode(1);
    root->left = createNode(5);
    root->right = createNode(2);
    root->left->left = createNode(-1);
    root->left->right = createNode(9);
    root->left->right->left = createNode(21);
    root->right->left = createNode(2);
    root->right->right = createNode(123);
    root->right->right->right = createNode(121);
    root->right->right->right->left = createNode(0);
    return root;
}

void printInorder(node *n)
{
    // implement this ...
}

void printPreorder(node *n)
{
    // implement this ...
}

void printPostorder(node *n)
{
    // implement this ...
}

int main(void)
{
    node *root = createHardCodedTree();
    // printInorder(root);
    // printPreorder(root);
    printPostorder(root);
    // once you implement your own queue:
    // printLevelOrder(root);
}