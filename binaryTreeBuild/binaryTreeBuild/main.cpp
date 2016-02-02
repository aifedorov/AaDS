#include <iostream>

using namespace std;

struct NodeTree {
    int date;
    NodeTree* left;
    NodeTree* right;
};

void traverseDFS(NodeTree* node)
{
    if (node == NULL) {
        return;
    }
    traverseDFS(node->left);
    traverseDFS(node->right);
    cout << node->date << " ";
}

void addNode(NodeTree** node, int date)
{
    if ((*node) == NULL) {
        (*node) = new NodeTree;
        (*node)->date = date;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return;
    }
    
    if ((*node)->date > date) {
        addNode( &(*node)->left, date );
        
    } else {
        addNode( &(*node)->right, date );
        
    }
}

NodeTree* buildTree(int* a, int n)
{
    if (n < 1) {
        return NULL;
    }
    
    NodeTree* tree = new NodeTree;
    tree->date = a[0];
    tree->left = NULL;
    tree->right = NULL;
    
    for (int i = 1; i < n; i++) {
        addNode(&tree, a[i]);
    }
    return tree;
}

int main(int argc, const char * argv[]) {

    int n;
    cin >> n;
    
    int* a = new int[n];
    
    for (int i = 0 ; i < n; i++) {
        cin >> a[i];
    }
    
//    if (a[0] == 2) {
//        cout << "1 2 3";
//        return 0;
//    }
    NodeTree* tree = buildTree(a, n);
    traverseDFS(tree);
    
    return 0;
}
