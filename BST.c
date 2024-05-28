#include    <stdio.h>
#include    <stdlib.h>

typedef struct BinaryTreeNode{
    int key;
    struct BinaryTreeNode *left, *right;
}BinaryTreeNode;

BinaryTreeNode* newNode(int key){
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

BinaryTreeNode* findMin(BinaryTreeNode* root){
    if (root==NULL)
        return NULL;
    else if (root->left!=NULL)
        return findMin(root->left);
    return root;
}

BinaryTreeNode* findMax(BinaryTreeNode* root){
    if (root==NULL)
        return NULL;
    else if (root->right!=NULL)
        return findMax(root->right);
    return root;
}

BinaryTreeNode* searchNode(BinaryTreeNode* root,int target){
    if (root==NULL)
        return NULL;
    if (root->key>target)
        return searchNode(root->left,target);
    else if(root->key<target)
        return searchNode(root->right,target);
    else
        return root;
}

BinaryTreeNode* insertNode(BinaryTreeNode* node,int value){
    if (node == NULL){
        BinaryTreeNode *temp = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
        temp->key = value;
        temp->left = temp->right = NULL;
        return temp;
    }
    if(value < node->key)
        node->left = insertNode(node->left,value);
    else if(value>node->key)
        node->right = insertNode(node->right,value);
    else
        ;
    return node;
}
BinaryTreeNode* delete(BinaryTreeNode* root,int x){
    //x가 BST 안에 없을 때, NULL 반환하며 그냥 종료
    if (root == NULL)
        return NULL;

    if(x > root->key)
        root->right = delete(root->right,x);
    else if(x < root->key)
        root->left = delete(root->left,x);
    else{
        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if(root->left == NULL || root->right ==NULL){
            BinaryTreeNode *temp;
            if(root->left == NULL)
                temp = root->right;
            else
                temp = root->left;
            free(root);
            return temp;
        }
        else{
            BinaryTreeNode *temp =findMin(root->right);
            root->key=temp->key;
            root->right = delete(root->right,temp->key);
        }
    }
}

int main(){
    BinaryTreeNode* root = newNode(10);
    insertNode(root,5);
    insertNode(root,10);
    insertNode(root,15);
    insertNode(root,3);
    insertNode(root,8);
    insertNode(root,12);
    insertNode(root,18);
    insertNode(root,17);
    insertNode(root,16);

    printf("%d\n",findMax(root)->key);
    delete(root,18);
    printf("%d\n",findMax(root)->key);
    delete(root,17);
    printf("%d\n",findMax(root)->key);
    delete(root,12);
    printf("%d\n",findMax(root)->key);
    return 0;
}