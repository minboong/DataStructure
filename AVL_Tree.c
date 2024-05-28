#include    <stdio.h>
#include    <stdlib.h>

#define MAX(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; })

typedef struct BinaryTreeNode{
    int key;
    struct BinaryTreeNode *left, *right;
    int height;
}BinaryTreeNode;

BinaryTreeNode* newNode(int key){
    BinaryTreeNode* node = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height=0;

    return (node);
}
int height(BinaryTreeNode* node){
    if(node==NULL)
        return -1;
    if(node->left==NULL&&node->right==NULL){
        node->height=0;
        return node->height;
    }
    else if(height(node->right)>=height(node->left)){
        node->height=node->right->height+1;
        return node->height;
    }
    else{
        node->height=node->left->height+1;
        return node->height;
    }
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


BinaryTreeNode *rightRotate(BinaryTreeNode *z){
    BinaryTreeNode *y = z->left;
    BinaryTreeNode *T3 = y->right;

    z->left = T3;
    y->right = z;

    z->height = MAX(height(z->left),height(z->right))+1;
    y->height = MAX(height(y->left),height(y->right))+1;
    
    return y;
}
BinaryTreeNode *leftRotate(BinaryTreeNode *z){
    BinaryTreeNode *y = z->right;
    BinaryTreeNode *T2 = y->left;

    z->right = T2;
    y->left = z;

    z->height = MAX(height(z->left),height(z->right))+1;
    y->height = MAX(height(y->left),height(y->right))+1;
    
    return y;
}
BinaryTreeNode* insert(BinaryTreeNode* node, int key){
    if (node==NULL)
        return(newNode(key));
    if(key < node->key){ //LL or LR
        node->left = insert(node->left, key);
        if(height(node->left)-height(node->right)>1){ //unbalanced
            printf("unbalanced\n");
            if(key < node->left->key) //LL
                return rightRotate(node);
            else{//LR
                BinaryTreeNode * y = node->left;
                node->left = leftRotate(y);
                return rightRotate(node);
            }
        }
    }
    else if(key > node-> key){
        node->right = insert(node->right, key);
        if(height(node->right)-height(node->left)>1){ //unbalanced
            printf("unbalanced\n");
            if(key > node->right->key) //RR
                return leftRotate(node);
            else{//RL
                BinaryTreeNode * y = node->right;
                node->right = rightRotate(y);
                return leftRotate(node);
            }
        }
    }
    node->height = 1 + MAX(height(node->left), height(node->right));
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
            root->key = temp->key;
            root->right = delete(root->right,temp->key);
        }
    }
    //AVL
    if (root==NULL)
        return NULL;
    root->height = 1 + MAX(height(root->left),height(root->right));

    if(height(root->left)-height(root->right)>1){
        if(height(root->left->left)>=height(root->left->right))
            return rightRotate(root);
        else{
            BinaryTreeNode *y = root->left;
            root->left = leftRotate(y);
            return rightRotate(root);
        }
    }
    else if(height(root->right)-height(root->left)>1){
        if(height(root->right->right)>=height(root->right->left))
            return leftRotate(root);
        else{
            BinaryTreeNode *y = root->right;
            root->right = rightRotate(y);
            return leftRotate(root);
        }
    }
    return root;
}
int main(){
    BinaryTreeNode* root = newNode(4);
    root=insert(root,2);
    root=insert(root,6);
    root=insert(root,1);
    root=insert(root,3);
    root=insert(root,5);
    root=insert(root,7);
    root=insert(root,16);
    root=insert(root,15);
    root=insert(root,14);
    root=insert(root,13);
    root=insert(root,12);
    root=insert(root,11);

    // printf("%d\n",root->right->left->key);
    // printf("%d\n",root->right->right->key);
    // printf("%d\n",root->right->right->left->key);
    

    // printf("%d\n",findMax(root)->key);
    // delete(root,18);
    // printf("%d\n",findMax(root)->key);
    // delete(root,17);
    // printf("%d\n",findMax(root)->key);
    // delete(root,12);
    // printf("%d\n",findMax(root)->key);
    printf("%d\n",root->key);
    printf("%d\n",findMax(root)->key);
    root=delete(root,11);
    root=delete(root,12);
    printf("%d\n",root->key);
    printf("%d\n",findMax(root)->key);
    return 0;
}