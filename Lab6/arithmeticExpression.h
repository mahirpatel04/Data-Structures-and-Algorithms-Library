#pragma once
#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode{
    char data;
    char key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char data, char key):data(data),key(key),left(0),right(0){}
};

class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;

  public:
    // Constructor
    arithmeticExpression(const string &);

    // Destructor which calls a private recursive helper function
    ~arithmeticExpression() {
        recursiveDestructor(root);
    }
    // Copy constructor and assignment operator set to delete since we don't use those
    arithmeticExpression(const arithmeticExpression&) = delete;
    arithmeticExpression operator=(const arithmeticExpression&) = delete;

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
    void buildTree();

    /* Calls the recursive infix function. */
    void infix();

    /* Calls the recursive prefix function. */
    void prefix();

    /* Calls the recursive postfix function. */
    void postfix();

    /* Calls the recursive visualizeTree function and generates the .png file using system call. */
    void visualizeTree(const string &);

 private:
    void recursiveDestructor(TreeNode* currNode) {
        if (currNode) {
            recursiveDestructor(currNode->left);
            recursiveDestructor(currNode->right);
            delete currNode;
        }
    }
    /* Helper function that returns an integer according to
       the priority of the given operator. */
    int priority(char);

    /* Helper function that returns the postfix notation equivalent
       to the given infix expression */
    string infix_to_postfix();

    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
    void infix(TreeNode *);

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
    void prefix(TreeNode *);

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void postfix(TreeNode *);

    /* Helper function for generating the dotty file. This is a recursive function. */
    void visualizeTree(ofstream &, TreeNode *);
};
