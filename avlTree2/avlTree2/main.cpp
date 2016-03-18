#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

struct command
{
    int type;
    int value;
};

struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

struct node* newNode(int key)
{
    struct node* node = (struct node*)
    malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    return x;
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    
    return y;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    
    node->height = max(height(node->left), height(node->right)) + 1;
    
    int balance = getBalance(node);
    
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    return node;
}

struct node * minValueNode(struct node* node)
{
    struct node* current = node;
    
    while (current->left != NULL)
        current = current->left;
    
    return current;
}

struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL)
        return root;
    
    if ( key < root->key )
        root->left = deleteNode(root->left, key);
    
    else if( key > root->key )
        root->right = deleteNode(root->right, key);
    
    else
    {
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;
            
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            
            free(temp);
        }
        else
        {
            struct node* temp = minValueNode(root->right);
            
            root->key = temp->key;
            
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL)
        return root;
    
    root->height = max(height(root->left), height(root->right)) + 1;
    
    int balance = getBalance(root);
    
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}

void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main()
{
    int n;
    cin >> n;
    
    vector<command> commands;
    string str;
    
    for (int i = 0; i < n; i++) {
        struct command cmd;
//        cin >> cmd.type;
//        cin >> cmd.value;
        commands.push_back(cmd);
        string tmp1, tmp2;
        cin >> tmp1;
        str+= tmp1;
        str+= " ";
        cin >> tmp2;
        str+= tmp2;
        str+= "\n";
    }
    
    cout << str;
    
//    struct node *root = NULL;
//    
//    for (int i = 0; i < n; i++) {
//        if (commands[i].type == 1) {
//            root = insert(root, commands[i].value);
//        }
//        if (commands[i].type == 2) {
//            root = deleteNode(root, commands[i].value);
//        }
//    }
//
//    preOrder(root);
    
    return 0;
}


1 41
1 18467
2 0
1 26500
1 19169
2 1
1 11478
1 29358
2 2
1 24464
1 5705
2 0
1 23281
1 16827
2 1


