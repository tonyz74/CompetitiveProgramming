#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string S;
    cin >> S;

    bool ok = true;

    for (int i = 2; i <= 16; i += 2) {
        int x = i - 1;
        if (S[x] != '0') {
            ok = false;
            break;
        }
    }

    if (ok) {
        cout << "Yes";
    } else {
        cout << "No";
    }
    cout << endl;
}