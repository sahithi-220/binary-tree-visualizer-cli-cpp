#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;

// ============================
// Function Declarations
// ============================

struct Node;

Node* insertLevelOrder(int arr[], int i, int n);
void printTree(Node* root, int space = 0, int height = 10);
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void levelOrder(Node* root);
int treeHeight(Node* root);
int countNodes(Node* root);
int countLeaves(Node* root);
bool search(Node* root, int key);
void deleteTree(Node* root);

// ============================
// Node Structure
// ============================

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// ============================
// Insert using Level Order
// ============================

Node* insertLevelOrder(int arr[], int i, int n) {
    if (i >= n) return nullptr;

    Node* root = new Node(arr[i]);
    root->left = insertLevelOrder(arr, 2 * i + 1, n);
    root->right = insertLevelOrder(arr, 2 * i + 2, n);
    return root;
}

// ============================
// Print Tree Visually (90° Rotated)
// ============================

void printTree(Node* root, int space, int height) {
    if (!root) return;

    space += height;
    printTree(root->right, space);

    cout << endl;
    for (int i = height; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    printTree(root->left, space);
}

// ============================
// Tree Traversals
// ============================

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelOrder(Node* root) {
    if (!root) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();
        cout << cur->data << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

// ============================
// Tree Operations
// ============================

int treeHeight(Node* root) {
    if (!root) return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

bool search(Node* root, int key) {
    if (!root) return false;
    if (root->data == key) return true;
    return search(root->left, key) || search(root->right, key);
}

void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ============================
// Main Function
// ============================

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    Node* root = insertLevelOrder(arr, 0, n);

    cout << "Binary Tree Visual Representation:\n";
    printTree(root);

    cout << "\n\nInorder Traversal: ";
    inorder(root);
    cout << "\nPreorder Traversal: ";
    preorder(root);
    cout << "\nPostorder Traversal: ";
    postorder(root);
    cout << "\nLevel Order Traversal: ";
    levelOrder(root);

    cout << "\n\nTree Height: " << treeHeight(root);
    cout << "\nTotal Nodes: " << countNodes(root);
    cout << "\nLeaf Nodes: " << countLeaves(root);

    int key = 5;
    cout << "\n\nSearch for " << key << ": " << (search(root, key) ? "Found" : "Not Found");

    // Memory cleanup
    deleteTree(root);
    return 0;
}

