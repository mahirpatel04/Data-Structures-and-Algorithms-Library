#include <iostream>
#include "BSTree.h"

using namespace std;


int main() {
    BSTree t;
    t.insert("G");
    t.insert("B");
    t.insert("A");
    t.insert("L");
    t.insert("Z");
    t.insert("G");
    t.debug();
    cout << endl;
    t.remove("Z");
    cout << endl;
    cout << endl;
    t.debug();
    cout << t.largest() << endl;
    return 0;
}