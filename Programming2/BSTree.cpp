#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
  // Edge case: tree is empty
  if (root == nullptr) {
    root = new Node(key);
    return;
  }
  for (Node* curr = root; curr!= nullptr;) {
    // Edge case: count is greater than 1
    if (curr->key == key) {
      curr->count++;
      return;
    }
    // If key is less than current then go to the left according to BST properties
    else if (key < curr->key) {
      if (curr->left == nullptr) {
        curr->left = new Node(key);
        return;
        };
      curr = curr->left;
    }
    // If key is greater than current then go to the right according to BST properties
    else if (key > curr->key)  {
      if (curr->right == nullptr) {
        curr->right = new Node(key);
        return;
        };
      curr = curr->right;
    }
  }
}

bool BSTree::search(const string& key) const {
  // If tree is empty then the specified key is not in the tree so return false
  if (root == nullptr) return false;
  // Traverse the tree and pick direction based on comparison with curr->key (left if smaller, right if larger)
  for (Node* curr = root; curr!= nullptr;) {
    if (curr->key > key) {
      curr = curr->left;
    }
    else if (curr->key < key) {
      curr = curr->right;
    }
    // Key found so return true
    else {
      return true;
    }
  }
  // Loop ends after traversing tree, so key not found
  return false;
}

string BSTree::largest() const {
  if (root == nullptr) throw runtime_error("Tree is empty");
  Node* curr = root;
  // Keep going right until you get to a leaf since right is greater in a BST
  while (curr->right != nullptr) {
    curr = curr->right;
  }
  return curr->key;
}

string BSTree::smallest() const {
  if (root == nullptr) throw runtime_error("Tree is empty");
  Node* curr = root;
  // Keep going left until you get to a leaf since left is smaller in a BST
  while (curr->left != nullptr) {
    curr = curr->left;
  }
  return curr->key;
}

int BSTree::height(const string& key) const {
  // First search for the key using same logic as BSTree::search()
  for (Node* curr = root; curr!= nullptr;) {
    if (curr->key > key) {
      curr = curr->left;
    }
    else if (curr->key < key) {
      curr = curr->right;
    }
    else {
      // Key is found so use helper function to return the height of the key found
      return height_of(curr, 0);
    }
  }
  // Have to return int so return -1 which is an invalid height to show that key was not found in the tree at all or tree is empty
  return -1;
}

void BSTree::remove(const string& key) {
  // Edge case: tree is empty cannot remove anything
  if (root == nullptr) {
    throw runtime_error("Tree is empty, cannot remove node");
  }
  // Edge case: key to remove not found in the tree
  if (!search(key)) {
    throw runtime_error("Node expected to remove not found in tree");
  }
  else{
        Node* nodePosition = root;        // points at node to remove
        Node* parentNode = nullptr;       // points to nodePosition's parent node

        // Use loop to set the pointers to the correct nodes. Similar logic to search()
        while((nodePosition != nullptr) && (nodePosition->key != key)){
            parentNode = nodePosition;
            if(key < nodePosition->key){
                nodePosition = nodePosition->left;
            }
            else{
                nodePosition = nodePosition->right;
            }
        }
        // Edge case: Count is greater than 1 so simply decrease by 1
        if(nodePosition->count > 1){
            nodePosition->count--;
            return;
        }
        // Typical Case: Use helper function to recursively remove the node
        else{
            remove(parentNode, nodePosition, key);
        }
    }
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
  // Edge Case: Root with no children
  // Just delete the root and set it to nullptr
  if((tree == root) && (tree->left == nullptr) && (tree->right == nullptr)){ 
      delete root;
      root = nullptr;
  }

  // Edge Case: Deleting leaf node
  else if ((tree->right == nullptr) && ((tree->left == nullptr))){ 
      // If node is left of parent then delete parent's left node
      if (parent->left == tree){
          parent->left = nullptr;
          delete tree;
      }
      // If node is right of parent then delete parent's right node
      else{
          parent->right = nullptr;
          delete tree;
      }
  }    
  // Edge Case: Deletes node with 2 children OR only left child 
  else if(((tree->right != nullptr) || ((tree->right == nullptr))) && (tree->left != nullptr)){
      Node* predNode = tree->left;
      Node* predParent = tree;
      // Finds the predecessor and its parent, by going as far right as possible in the left subtree
      // This finds the greatest node on the left side
      while(predNode->right != nullptr){
          predParent = predNode;
          predNode = predNode->right;
      }
      // Replaces values
      tree->key = predNode->key;
      tree->count = predNode->count;
      // Recursively removes the duplicate node
      remove(predParent, predNode, key);
  } 

  //to delete a node with only right child-> replaces with the successor
  else if ((tree->right != nullptr) && (tree->left == nullptr)){ 
      Node* succNode = tree->right;
      Node* succParent = tree;
      // Finds the successor and its parent, by going as far left as possible in the right subtree
      // This finds the smallest node on the right side
      while(succNode->left != nullptr){
          succParent = succNode;
          succNode = succNode->left;
      }
      // Replaces values
      tree->key = succNode->key;
      tree->count = succNode->count;
      // Recursively removes the duplicate node
      remove(succParent, succNode, key);
  }
}

int BSTree::height_of(Node* tree, int height) const {
  // Base case: Tree is a leaf
  if ((tree->left == nullptr) and (tree->right == nullptr)) {
    return height;
  }
  // Recursive case: Only left node exists so recursively call height_of on the left node
  else if ((tree->left != nullptr) and (tree->right == nullptr)) {
    return height_of(tree->left, height +1);
  }
  // Recursive case: Only right node exists so recursively call height_of on the right node
  else if ((tree->right != nullptr) and (tree->left == nullptr)) {
    return height_of(tree->right, height + 1);
  }
  // Recursive case: Has both children so call height_of on both children and return the larger value
  else {
    return max(height_of(tree->left, height + 1), height_of(tree->left, height + 1));
  }
}

void BSTree::preOrder() const {
  if (root == nullptr) {
    cout << endl;
    return;
  }
  // Output root's payload at the very beginning then use helper function on left side then right side
  cout << root->key << "(" << root->count << ")" << ", ";
  preOrder(root->left);
  preOrder(root->right);
  cout << endl;
}

void BSTree::preOrder(Node* tree) const {
  if (tree == nullptr) return;    // Tree is empty so nothing to output, simply return
  // Output tree's payload then make recursive call on left side then right side
  cout << tree->key << "(" << tree->count << ")" << ", ";
  preOrder(tree->left);
  preOrder(tree->right);
}

void BSTree::postOrder() const {
  if (root == nullptr) {
    cout << endl;
    return;
  }
  // Use helper function on left side then right side, and then output root's payload at the very end
  postOrder(root->left);
  postOrder(root->right);
  cout << root->key << "(" << root->count << ")" << ", ";
  cout << endl;
}

void BSTree::postOrder(Node* tree) const {
  if (tree == nullptr) return;    // Tree is empty so nothing to output, simply return
  // Make recursive call on left side then right side, and then output tree's payload
  postOrder(tree->left);
  postOrder(tree->right);
  cout << tree->key << "(" << tree->count << ")" << ", ";
}

void BSTree::inOrder() const {
  if (root == nullptr) {
    cout << endl;
    return;
  }
  // Use helper function on left side, output root's payload, then use helper function on right side
  inOrder(root->left);
  cout << root->key << "(" << root->count << ")" << ", ";
  inOrder(root->right);
  cout << endl;
}

void BSTree::inOrder(Node* tree) const {
  if (tree == nullptr) return;    // Tree is empty so nothing to output, simply return
  // Recursively call on left side, output tree's payload, then recursively call right side
  inOrder(tree->left);
  cout << tree->key << "(" << tree->count << ")" << ", ";
  inOrder(tree->right);
}