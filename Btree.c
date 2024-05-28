#include    <stdio.h>
#include    <stdlib.h>

typedef struct tNode{
    int data;
    struct tNode* left;
    struct tNode* right;
}tNode;

tNode* newNode(int data){
    tNode* node = (tNode*)malloc(sizeof(tNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

void printInorder(tNode* node){
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d ",node->data);
    printInorder(node->right);
}
void printPreorder(tNode* node){
    if (node == NULL)
        return;
    printf("%d ",node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}
void printPostorder(tNode* node){
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d ",node->data);
}

int main(){
    tNode* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printInorder(root);
    printf("\n");
    printPreorder(root);
    printf("\n");
    printPostorder(root);
    printf("\n");

    return 0;
}