#include <iostream>

using namespace std;

struct Node {
    int value;
    int priority;
    Node* left;
    Node* right;
    
    Node(){}
    Node(int value) : value(value), priority(0), left(NULL), right(NULL) {}
    Node(int value, int priority) : value(value), priority(priority), left(NULL), right(NULL) {}
    Node(int value, int priority, Node* left, Node* right) : value(value), priority(priority), left(left), right(right) {}
};

struct InputElem {
    int value;
    int priority;
};

Node* findNode(Node* node, int value)
{
    if (node == NULL) {
        return NULL;
    }
    
    if (node->value == value ) {
        return node;
    }
    if (node->value > value) {
        return findNode( node->left, value);
    } else {
        return findNode( node->right, value);
    }
}

void insertNode(Node*& node, int value)
{
    if ( node == NULL ) {
        node = new Node(value);
        return;
    }
    
    if ( node->value > value ) {
        insertNode( node->left, value );
    } else {
        insertNode( node->right, value );
    }
}

int depthTree(Node* node, int sum)
{
    if (node == NULL) {
        return sum;
        
    } else {
        ++sum;
    }
    
    int leftDepth = 0, rightDepth = 0;
    leftDepth = depthTree(node->left, sum);
    rightDepth = depthTree(node->right, sum);
    
    return leftDepth > rightDepth ? leftDepth : rightDepth;
}

void splitTree(Node* currentNode, int value, Node*& left, Node*& right )
{
    if (currentNode == NULL) {
        left = NULL;
        right = NULL;
        
    } else if ( currentNode->value <= value ) {
        splitTree( currentNode->right, value, currentNode->right, right );
        left = currentNode;
        
    } else {
        splitTree( currentNode->left, value, left, currentNode->left );
        right = currentNode;
        
    }
}

void insertTreap(Node*& node, int value, int priority)
{
    if (node == NULL) {
        node = new Node(value, priority);
        return;
    }
    
    if ( node->priority < priority ) {
        Node *left, *right;
        splitTree(node, value, left, right);
        Node* newNode = new Node(value, priority, left, right);
        node = newNode;
        return;
        
    }
    if (node->value > value) {
        insertTreap( node->left, value, priority );
        return;
        
    } else {
        insertTreap( node->right, value, priority);
        return;
        
    }
}

int main(int argc, const char * argv[]) {
    
    int n;
    cin >> n;
    
    InputElem* A = new InputElem[n];
    
    for (int i = 0; i < n; i++) {
        cin >> A[i].value;
        cin >> A[i].priority;
    }
    
    Node* nodeTree = new Node();
    nodeTree = NULL;

    Node* nodeTreap = new Node();
    nodeTreap = NULL;
    
    for (int i = 0; i < n; i++) {
        insertNode(nodeTree, A[i].value);
        insertTreap(nodeTreap, A[i].value, A[i].priority);
    }

    cout << depthTree(nodeTree, 0) - depthTree(nodeTreap, 0) << endl;
    
    return 0;
}
