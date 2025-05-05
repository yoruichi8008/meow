#include <iostream>
using namespace std;
class Node {
public:
int data;
Node *left, *right;
bool lthread, rthread;
Node(int value) {
data = value;
left = right = nullptr;
lthread = rthread = true;
}
};
class ThreadedBinaryTree {
Node* root;
public:
ThreadedBinaryTree() {
root = nullptr;
}
void insert(int key) {
Node* ptr = root;
Node* parent = nullptr;
while (ptr != nullptr) {
if (key == ptr->data) {
cout << "Duplicate key not allowed\n";
return;
}
parent = ptr;
if (key < ptr->data) {
if (!ptr->lthread)
ptr = ptr->left;
else
break;
} else {
if (!ptr->rthread)
ptr = ptr->right;
else
break;
}
}
Node* newNode = new Node(key);
if (parent == nullptr) {
root = newNode;
} else if (key < parent->data) {
newNode->left = parent->left;
newNode->right = parent;
parent->lthread = false;
parent->left = newNode;
} else {
newNode->left = parent;
newNode->right = parent->right;
parent->rthread = false;
parent->right = newNode;
}
}
void inorder() {
Node* cur = root;
while (cur && !cur->lthread)
cur = cur->left;
while (cur) {
cout << cur->data << " ";
cur = inorderSuccessor(cur);
}
cout << endl;
}
Node* inorderSuccessor(Node* ptr) {
if (ptr->rthread)
return ptr->right;
ptr = ptr->right;
while (ptr && !ptr->lthread)
ptr = ptr->left;
return ptr;
}
};
int main() {
ThreadedBinaryTree tbt;
int choice, val;
cout << "Threaded Binary Tree\n";
do {
cout << "\n1. Insert node\n2. Inorder Traversal\n3. Exit\nEnter choice: ";
cin >> choice;
switch (choice) {
case 1:
cout << "Enter value to insert: ";
cin >> val;
tbt.insert(val);
break;
case 2:
cout << "Inorder Traversal: ";
tbt.inorder();
break;
case 3:
cout << "Exiting...\n";
break;
default:
cout << "Invalid choice!\n";
}
} while (choice != 3);
return 0;
}