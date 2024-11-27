#pragma once

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree();
  ~Tree();
  Tree(const Tree&) = delete;
  Tree operator=(const Tree&) = delete;
  void insert(const string &);
  void preOrder() const;
  void inOrder() const;
  void postOrder() const;
  void remove(const string &);
  bool search (const string &) const;

private:
  void RecursiveDestructor(Node*);
  Node* locate(const string&) const;
  void preOrder(Node* currNode) const;
  void inOrder(Node* currNode) const;
  void postOrder(Node* currNode) const;
};
