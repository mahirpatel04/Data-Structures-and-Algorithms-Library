#include "Tree.h"
#include <iostream>

using namespace std;

Tree::Tree(): root(nullptr) {}
void Tree::insert(const string& newKey) {
    if (search(newKey)) return;

    if (root == nullptr) {
        root = new Node(newKey);
        return;
    }
    // Traverse to the right node where the Node should be inserted
    // The logic here is very simlilar to locate() except we check the next node's values instead of curr's values

    Node* currNode = root;
    while (currNode->left != nullptr) {
        if (currNode->hasTwoStrings()) {
            if (newKey < currNode->small) {
                currNode = currNode->left;
            }
            else if (newKey < currNode->large) {
                currNode = currNode->middle;
            }
            else {
                currNode = currNode->right;
            }
        }
        else {
            if (newKey < currNode->small) {
                currNode = currNode->left;
            }
            else {
                currNode = currNode->middle;
            }
        }
    }
    // If it only has one string then use insertIntoNode() to just put it into the node then return
    if (!currNode->hasTwoStrings()) {
        currNode->insertIntoNode(newKey);
        return;
    }
    // If there are already 2 strings then use split() to split the nodes by moving the middle value key into the parents
    else {
        // If root then set root to be currNode
        if (currNode->parent == nullptr) {
            currNode->split(newKey);
            root = currNode;
        }
        else {
            currNode->split(newKey);
        }
    }
    
}

void Tree::preOrder() const {
    // Call helper
    preOrder(root);
    cout << endl;
}
void Tree::inOrder() const {
    // Call helper
    inOrder(root);
    cout << endl;
}
void Tree::postOrder() const {
    // Call helper
    postOrder(root);
    cout << endl;
}

void Tree::preOrder(Node* currNode) const {
    // Output first, then call on children
    if (currNode == nullptr) return;
    // If two strings, then 3 pointers to also output
    if (currNode->hasTwoStrings()) {
        cout << currNode->small << ", ";
        preOrder(currNode->left);
        cout << currNode->large << ", ";
        preOrder(currNode->middle);
        preOrder(currNode->right);
    }
    // If one string, then only 2 pointers to also output
    else {
        cout << currNode->small << ", ";
        preOrder(currNode->left);
        preOrder(currNode->middle);
    }
}
void Tree::inOrder(Node* currNode) const {
    // Call on child, output, call on next child
    if (currNode == nullptr) return;
    inOrder(currNode->left);
    cout << currNode->small << ", ";
    inOrder(currNode->middle);
    // If two strings, then right also needs to be output
    if (currNode->hasTwoStrings()) {
        cout << currNode->large << ", ";
        inOrder(currNode->right);
    }
}

void Tree::postOrder(Node* currNode) const {
    // Call on children, then output
    if (currNode == nullptr) return;
    // If two strings, then 3 pointers to also output
    if (currNode->hasTwoStrings()) {
        postOrder(currNode->left);
        postOrder(currNode->middle); 
        cout << currNode->small << ", "; 
        postOrder(currNode->right); 
        cout << currNode->large << ", ";
    }
    // Only 2 pointers if there is 1 string
    else {
        postOrder(currNode->left);
        postOrder(currNode->middle);
        cout << currNode->small << ", ";
    }    
}

void Tree::remove(const string &targetKey) {
    // Get location of the targetNode using locate()
    Node* targetNode = locate(targetKey);
    // If location not found then just return because you cannot remove a key that doesn't exist
    if (targetNode == nullptr) return;
    if (targetNode->hasTwoStrings()) {
        // If the targetNode has two strings then just delete the targetKey and swap if targetKey was smaller
        if (targetKey == targetNode->small) {
            targetNode->small = targetNode->large;
            targetNode->large = "";
        }
        else {
            targetNode->large = "";
        }
    }
    else {
        Node* parentNode = targetNode->parent;
        // Check is targetKey is at the root
        if (parentNode) {
            // Shift nodes depending on relationships of keys in parentNode and targetNode
            if (parentNode->small > targetKey) {
                parentNode->left = nullptr;
                parentNode->large = parentNode->middle->small;
                parentNode->middle = nullptr;
            }
            else {
                parentNode->middle = nullptr;
                parentNode->large = parentNode->small;
                parentNode->small = parentNode->left->small;
                parentNode->left = nullptr;
            }
        }
        else {
            // Create new node
            Node* insertNode = new Node("");
            // If left side exists (there will also be a right side for sure) then make 
            // combine nodes and make the new node the root
            if (root->left) {
                insertNode->small = root->left->small;
                insertNode->large = root->middle->small;
                root = insertNode;
            }
            // If there is not left side then just delete the node and set root to be nullptr
            else {
                delete targetNode;
                root = nullptr;
            }
        }
    }
}
    

bool Tree::search(const string &targetKey) const {
    // Since locate returns a pointer to Node with targetKey
    // if locate is nullptr then the key is not found so return False.
    // If there is a proper pointer we can return True.
    return locate(targetKey) != nullptr;
  }

  // Function returns pointer to Node in tree with targetKey passed in
  Node* Tree::locate(const string& targetKey) const {
    // If tree is empty there's nothing to locate so return nullptr
    if (root == nullptr) return nullptr;
    // Traverse the tree using basic BST properties (left is less, right is large)
    Node* currNode = root;
    while (currNode != nullptr) {
        // If it has two strings then there are three possible pointers where targetNode may be
        if (currNode->hasTwoStrings()) {
            if ((targetKey == currNode->small) or (targetKey == currNode->large)) {
                return currNode;
            }
            else if (targetKey < currNode->small) {
                currNode = currNode->left;
            }
            else if (targetKey < currNode->large) {
                currNode = currNode->middle;
            }
            else if (targetKey > currNode-> large) {
                currNode = currNode->right;
            }
        }
        // If it only has one string then only two possible pointers where targetNode may be
        else {
            if (targetKey == currNode->small) {
                return currNode;
            }
            if (targetKey < currNode->small) {
                currNode = currNode->left;
            }
            else if (targetKey > currNode->small) {
                currNode = currNode->middle;
            }
        }
    }
    return nullptr;
  }

Tree::~Tree() {
    RecursiveDestructor(root);
}

void Tree::RecursiveDestructor(Node* currentNode) {
    // Check is current node is nullptr, if it is then don't need to do anything
    if (currentNode != nullptr) {
        // Recursively delete the subtrees
        RecursiveDestructor(currentNode->left);
        RecursiveDestructor(currentNode->middle);
        RecursiveDestructor(currentNode->right);
        // Delete the  current node
        delete currentNode;
    }
}
