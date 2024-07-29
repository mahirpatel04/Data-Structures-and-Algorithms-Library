#include "Node.h"
#include <stdexcept>
#include <iostream>

using namespace std;
// Constructor
Node::Node(const string& key): small(key), left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) {
}

bool Node::hasTwoStrings() {
    // Checks if a certain node has two strings
    return (!small.empty() and !large.empty());
}

bool Node::hasThreeKids() {
    // Checks if a certain node has three children
    return (left and middle and right);
}

void Node::insertIntoNode(const string& key) {
    // Helper function to help insert
    // Can't insert a key into a node if it has two strings already
    if (hasTwoStrings()) throw runtime_error("Trying to add key to a full node");
    // If key is smaller then switch around the keys
    if (key < small) {
        large = small;
        small = key;
    }
    // If it is greater then simply set large to be key
    else {
        large = key;
    }
}

void Node::split(const string& key) {
    // HELPER FUNCTION: Used to split Node's depending on relationship of parameter key and keys within the Node
    
    // Base case where Node doesn't have two strings so you simply put the key back in
    if (!hasTwoStrings()) {
        insertIntoNode(key);
        return;
    }
    // Checking if Node is the root
    else if (parent == nullptr) {
        // If key is less than small then small will get moved up into the next level
        if (key < small) {
            Node* smallNode = new Node(key);
            Node* largeNode = new Node(large);
            smallNode->left = left;
            largeNode->left = right;
            // Remove large
            large = "";
            left = smallNode;
            middle = largeNode;
            // Setting the parent of the two nodes to be original node
            smallNode->parent = this;
            largeNode->parent = this;
        }
        else if (key > large) {
            // If key is greater than large then large will get moved up into the next level
            Node* smallNode = new Node(small);
            Node* largeNode = new Node(key);
            smallNode->left = left;
            largeNode->left = right;
            // Copy large into small then delete large
            small = large;
            large = "";
            left = smallNode;
            middle = largeNode;
            // Set the parents to be original node
            smallNode->parent = this;
            largeNode->parent = this;
        }
        else {
            // This means the new key is in the middle which means middle will get moved up into the next level
            Node* smallNode = new Node(small);
            Node* largeNode = new Node(large);
            smallNode->parent = this;
            largeNode->parent = this;
            smallNode->left = left;
            largeNode->left = right;
            // Set small to be key and delete large (essentially getting rid of small/large and only keeping key)
            small = key;
            large = "";
            // Set the child pointers correctly depending on how many children the node has
            if (!hasThreeKids()) {
                left = smallNode;
                middle = largeNode;
            }
            else {
                left = smallNode;
                right = largeNode;
            }
        }
    }
    // Inserting if Node doesn't have 1 string AND Node is not the root
    else {
        // Check if the key to move into next level is small, large, or targetKey
        if (key < small) {
            if (parent->hasThreeKids()) {
                // Create new node
                Node* newNode = new Node(key);
                // Since key is less than small, the middle one ends up being small so move that up
                // by recursively calling split
                parent->split(small);
                // Adjust the node
                small = large;
                large = "";
                // Insert the newNode into the parent's left side
                parent->left->middle = newNode;
                newNode->parent = parent->left;

                parent->right->middle = parent->right->left;
                parent->right->left = this;
                
                parent->middle = parent->right;
                parent->right = nullptr;
            }
            else {
                // Simply split the parent after moving split up
                parent->split(small);
                small = key;
            }
        }
        else if (key > large) {
            // Key that will go up is large since the key is larger than large
            if (parent->hasThreeKids()) {
                // Move large key up to split with parents
                parent->split(large);
                large = key;
            }
            else {
                parent->large = large;
                large = "";
                parent->right = new Node(key);
            }
        }
        else {
            if (parent->hasThreeKids()) {
                // If there are three kids simply return
                return;
            }
            else {
                // Otherwise split after moving the key up since it is less than large and greater than small
                parent->split(key);
            }
        }

    }
}