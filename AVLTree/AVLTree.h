#pragma once
#include "Node.h"

class AVLTree {
  public:
    // Constructor
    AVLTree();
    // Destructor
    ~AVLTree();
    // Copy constructor and Assignment operator
    AVLTree(const AVLTree&) = delete;
    AVLTree operator=(const AVLTree&) = delete;

    void insert(const string& key);
    int balanceFactor(Node* node) const;
    void printBalanceFactors() const;

  private:
    Node* root;

    void deleteTree(Node* node);
    void updateHeight(Node* node);
    bool setChild(Node* node, string whichChild, Node* child);
    bool replaceChild(Node* node, Node* givenChild, Node* insertChild);
    void rotate(Node* node);
    void rotateLeft(Node* node);
    void rotateRight(Node* node);
    void printBalanceFactors(Node* node) const;
};