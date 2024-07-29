#include "arithmeticExpression.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <stack>

using namespace std;

// Constructor
arithmeticExpression::arithmeticExpression(const string & userString): infixExpression(userString), root(nullptr) {}

// Helper function provided by ZyBooks
int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

// Helper function provided by ZyBooks
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

// Helper function provided by ZyBooks
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

// Calls the helper version of infix()
void arithmeticExpression::infix() {
    infix(root);
}


void arithmeticExpression::infix(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        // If operator then outputs parentheses
        if (currentNode->data == '+' || currentNode->data == '-' || currentNode->data == '/' || currentNode->data == '*') {
            cout << '(';
        }
        // Performs operations IN ORDER and parentheses help maintain priority
        infix(currentNode->left);
        cout << currentNode->data;
        infix(currentNode->right);
        if (currentNode->data == '+' || currentNode->data == '-' || currentNode->data == '/' || currentNode->data == '*') {
            cout << ')';
        }
    }
}

// Calls the helper version of prefix()
void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        // Outputs the current node then does left and right
        cout << currentNode->data;
        prefix(currentNode->left);
        prefix(currentNode->right);
    }
}

// Calls the helper version of postfix()
void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode* currentNode) {
    if (currentNode != nullptr) {
        // Outputs the left and right and then outputs the current node
        postfix(currentNode->left);
        postfix(currentNode->right);
        cout << currentNode->data;
    }
}

void arithmeticExpression::buildTree() {
    infixExpression = infix_to_postfix();
    stack<TreeNode*> s;
    // For loop that runs for the length of the expression
    for (unsigned i = 0; i < infixExpression.length(); i++) {
        TreeNode* currentNode = new TreeNode(infixExpression.at(i), 'a' + i);
        // If the current character is just a number then simply push onto the stack
        if (priority(infixExpression.at(i)) == 0) {
            s.push(currentNode);
        }
        else {
            // Get the operands out of the stack, update the tree to contain the operands, and then push the tree into the stack
            TreeNode* rightOperand = s.top();
            s.pop();
            TreeNode* leftOperand = s.top();
            s.pop();
            currentNode->left = leftOperand;
            currentNode->right = rightOperand;
            s.push(currentNode);
        }
    }
    // Set root to be the top of the stack since that is where our first expression will be
    root = s.top();
}

void arithmeticExpression::visualizeTree(ofstream &out, TreeNode *currentNode) {
    // Outputs the contents of a tree using recursion
    if (currentNode != nullptr) {
        // First output the current node's contents then output left and right
        out << "\t" << currentNode->key << endl;
        if (currentNode->left != nullptr) {
            out << "\t" << currentNode->key << " -> " << currentNode->left->key << endl;
        }
        if (currentNode->right != nullptr) {
            out << "\t" << currentNode->key << " -> " << currentNode->right->key << endl;
        }
        // Recursively call on the left and right nodes of the tree as well
        visualizeTree(out, currentNode->left);
        visualizeTree(out, currentNode->right);
    }
}