#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    int v;
    int old = -1;
    for (int i = 0; i < N; i++) {
        cin >> v;
        if (i != 0 && v != old) {
            cout << "No" << endl;
            return 0;
        }
        old = v;
    }

    cout << "Yes" << endl;
}