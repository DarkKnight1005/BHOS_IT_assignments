#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

typedef struct Node{
	int val;
	struct Node *left;
	struct Node *right;
} Node_t;

Node_t* newNode(int val){
    Node_t *node = (Node_t*) malloc(sizeof(struct Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return (node);

}
int max(int a, int b){

    return a > b ? a : b;
}

int findMax(Node_t *root, int maxx){

    if(root == NULL){
        return 0;
    }
    
    int left = findMax(root->left, maxx);
    int right = findMax(root->right, maxx);
    
    int maxima = max(max(left, right) + root->val, root->val);

    int maximum = max(maxima, left + right + root->val);
    
    if(maximum > maxx){
        maxx = maximum;
    }
    
    return maxima;

}

int main(){

    int maxx = INT32_MIN;
    Node_t* root = newNode(1);
    root->left = newNode(5);
    root->right = newNode(10);
    root->left->left = newNode(20);
    root->left->right = newNode(4);
    root->left->left->left = newNode(999);
    root->right->right = newNode(20);
    root->right->right->right = newNode(15);
    root->right->left = newNode(21);
    root->right->left = newNode(13);

    int ans = findMax(root, maxx);

    printf("%d", ans);

    return 0;
}