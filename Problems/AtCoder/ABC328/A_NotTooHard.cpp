#include <iostream>

using namespace std;
int main(void) {

    int N, X; cin >> N >> X;   

    int tot = 0;
    for (int i = 0; i < N; i++) {
        int A; cin >> A;
        if (A <= X) tot += A;
    }

    cout << tot << endl;
}