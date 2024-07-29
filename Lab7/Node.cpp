#include <iostream>
#include <string>
#include "Node.h"

//constructor
Node::Node(string userKey) :
 height(0), key(userKey), left(nullptr), right(nullptr), parent(nullptr) {
}