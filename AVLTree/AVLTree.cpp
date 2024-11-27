#include "AVLTree.h"
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;


AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    // Recursively delete all nodes in the tree.
    deleteTree(root);
}
void AVLTree::deleteTree(Node* currentNode) {
    // Check if the current node is null.
    if (currentNode == nullptr) return;

    // Recursively delete both subtrees.
    deleteTree(currentNode->left);
    deleteTree(currentNode->right);

    // Delete the current node.
    delete currentNode;
}

void AVLTree::insert(const string& target) {
    // Make new node
    Node* insertNode = new Node(target);
    Node* currentNode = root;

    // If the tree is empty, make the new node the root
    if (root == nullptr) {
        root = insertNode;
        return;
    }

    // Find node where the insert should take place and double check that the key doesn't already exist
    while (currentNode != nullptr) {
        // Left if the curr key > target
        if (currentNode->key > target) currentNode = currentNode->left;
        // Right if the curr key < target
        else if (currentNode->key < target) currentNode = currentNode->right;
        // Key is equal meaning we can't insert it
        else return;
    }
    

  // Reset currentNode to root
  currentNode = root;

  // Find the appropriate parent node to attach the new node
  while (currentNode != nullptr) {
    // Traverse left if the current node's key is greater than the target
    if (currentNode->key > target) {
      // Attach the node as the left child if the left child is nullptr
      if (currentNode->left == nullptr) {
        currentNode->left = insertNode;
        insertNode->parent = currentNode;
        currentNode = nullptr;
      }
      else {
        currentNode = currentNode->left;
      }
    }
    // Traverse right if the current node's key is less than or equal to the target
    else {
      // Attach the new node as the right child if the right child is nullptr
      if (currentNode->right == nullptr) {
        currentNode->right = insertNode;
        insertNode->parent = currentNode;
        currentNode = nullptr;
      }
      else {
        currentNode = currentNode->right;
      }
    }
  }

  // Start rebalancing the tree by performing rotations
  insertNode = insertNode->parent;
  while(insertNode != nullptr) {
    rotate(insertNode);
    insertNode = insertNode->parent;
  }
}


int AVLTree::balanceFactor(Node* currentNode) const {
    // Initialize the heights of the left and right subtrees
    int leftHeight = -1;
    int rightHeight = -1;

    // Check if the child exists and update its height
    if (currentNode->left != nullptr) leftHeight = currentNode->left->height;
    if (currentNode->right != nullptr) rightHeight = currentNode->right->height;

    // Return the difference
    return leftHeight - rightHeight;
}

void AVLTree::printBalanceFactors() const {
  // Call helper
  printBalanceFactors(root);
  cout << endl;
}

void AVLTree::printBalanceFactors(Node* currentNode) const {
  if (currentNode != nullptr) {
    // Recursively traverse the left subtree, print key and balance factor, then traverse right subtree
    printBalanceFactors(currentNode->left);
    cout << currentNode->key << "(" << balanceFactor(currentNode) << "), ";
    printBalanceFactors(currentNode->right);
  }
}


void AVLTree::rotate(Node* currentNode) {
  // Update height of current node
  updateHeight(currentNode);

  // Perform a rotation if the balance factor is -2 or 2
  if (balanceFactor(currentNode) == -2) {
    // Right-Right case
    if (balanceFactor(currentNode->right) == 1) {
      // Rotate right child towards right
      rotateRight(currentNode->right);
    }

    // Rotate current node left
    rotateLeft(currentNode);
  }
  else if (balanceFactor(currentNode) == 2) {
    // Left-Left case
    if (balanceFactor(currentNode->left) == -1) {
      // Rotate left child towards left
      rotateLeft(currentNode->left);
    }
    // Rotate current node right
    rotateRight(currentNode);
  }
}

void AVLTree::rotateRight(Node* currentNode) {
  // Store the right child of the left child
  Node* leftRightChild = currentNode->left->right;
  // Check if the current node has a parent
  if (currentNode->parent != nullptr) {
    // Replace the current node with its left child in the parent's children
    replaceChild(currentNode->parent, currentNode, currentNode->left);
  }
  else {
    // Current node is root so update root to be left child
    root = currentNode->left;
    root->parent = nullptr;
  }

  // Set the left child's right child as the current node
  setChild(currentNode->left, "right", currentNode);

  // Set the current node's left child as the leftRightChild
  setChild(currentNode, "left", leftRightChild);
}

void AVLTree::rotateLeft(Node* currentNode) {
  // Store the left child of the right child
  Node* rightLeftChild = currentNode->right->left;
  // Check if the current node has a parent
  if (currentNode->parent != nullptr) {
    // Replace the current node with its right child in the parent's children
    replaceChild(currentNode->parent, currentNode, currentNode->right);
  }
  else {
    // Current node is the root so update root to be right child
    root = currentNode->right;
    root->parent = nullptr;
  }

  // Set the right child's left child as the current node
  setChild(currentNode->right, "left", currentNode);

  // Set the current node's right child as the rightLeftChild
  setChild(currentNode, "right", rightLeftChild);
}

bool AVLTree::setChild(Node* currentNode, string whichChild, Node* child) {
  // Check if the child position is valid
  if (whichChild != "left" && whichChild != "right") {
    return false;
  }

  // Set child based on position
  if (whichChild == "left") {
    currentNode->left = child;
  }
  else {
    currentNode->right = child;
  }

  // Update the parent-child relationship
  if (child != nullptr) {
    child->parent = currentNode;
  }

  // Update the height of the current node
  updateHeight(currentNode);

  return true;
}

bool AVLTree::replaceChild(Node* currentNode, Node* givenChild, Node* insertChild) {
  // Check if the givenChild is the left child of the currentNode
  if (currentNode->left == givenChild) {
    // Call setChild to replace the left child with the insertChild
    return setChild(currentNode, "left", insertChild);
  }
  // Check if the givenChild is the right child of the currentNode
  else if (currentNode->right == givenChild) {
    // Call setChild to replace the right child with the insertChild
    return setChild(currentNode, "right", insertChild);
  }
  // No matching child found, return false
  return false;
}

void AVLTree::updateHeight(Node* currentNode) {
  // Initialize the heights of the left and right subtrees
  int leftHeight = -1;
  int rightHeight = -1;

  // Check if the left child exists and update its height
  if (currentNode->left != nullptr) {
    leftHeight = currentNode->left->height;
  }

  // Check if the right child exists and update its height
  if (currentNode->right != nullptr) {
    rightHeight = currentNode->right->height;
  }

  // Update the height of the current node based on the maximum height of its children
  currentNode->height = max(leftHeight, rightHeight) + 1;
}