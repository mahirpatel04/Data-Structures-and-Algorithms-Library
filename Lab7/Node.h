#pragma once
#include <string>
using namespace std;

struct Node {
    // Constructor
    Node(string);

    // Data
    int height;
    string key;

    // Connected Nodes
    Node* left;
    Node* right;
    Node* parent;
};
