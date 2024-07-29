#pragma once

#include <string>

using namespace std;

class Node {
  friend class Tree;
  Node(const string& key);

private:
  string small;
  string large;

  Node *left;
  Node *middle;
  Node *right;
  Node *parent;
  
  bool hasTwoStrings();
  bool hasThreeKids();
  void insertIntoNode(const string& key);
  void split(const string& key);
};
