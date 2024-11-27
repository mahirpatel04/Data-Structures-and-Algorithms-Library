#include "Jug.h"
#include <iostream>

using namespace std;

int main() {
    // MAIN COPY-PASTED FROM ZYBOOKS
    string answer;
    Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
    if (head.solve(answer) != 1){
        cout << "Error 3" << endl;
    }
    cout << answer<< endl ;
    cout<< endl;
    string secondAnswer;
    Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);

    if (head2.solve(secondAnswer) != 1){
        cout << "Error 3" << endl;
    }
    cout << secondAnswer << std::endl;
    return 0;
}