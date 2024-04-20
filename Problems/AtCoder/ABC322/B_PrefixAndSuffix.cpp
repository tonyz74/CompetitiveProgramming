#include <iostream>
#include <string>

using namespace std;

int main(void) {
    int N, M; cin >> N >> M;
    string S, T; cin >> S >> T;

    bool is_prefix = true;
    for (int i = 0; i < N; i++) {
        if (S[i] != T[i]) {
            is_prefix = false;
            break;
        }
    }

    bool is_suffix = true;
    for (int i = 0; i < N; i++) {
        if (S[i] != T[M - N + i]) {
            is_suffix = false;
            break;
        }
    }

    if (is_prefix && is_suffix) {
        cout << 0 << endl;
    } else if (is_prefix) {
        cout << 1 << endl;
    } else if (is_suffix) {
        cout << 2 << endl;
    } else {
        cout << 3 << endl;
    }
}