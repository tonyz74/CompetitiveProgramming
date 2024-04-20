#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
    int N; cin >> N;
    string S; cin >> S;

    vector<bool> B;
    for (int i = 0; i < N; i += 2) {
        if (S[i] == S[i + 1]) {
            continue;
        } else if (S[i] == 'H' && S[i + 1] == 'G') {
            if (B.size() == 0 || B.back() != 0) B.push_back(0);
        } else {
            if (B.size() == 0 || B.back() != 1) B.push_back(1);
        }
    }

    if (B.size() == 0) {
        printf("FAIL!\n");
        exit(-1);
    }

    int n_ones = 0;
    for (bool x: B) {
        if (x == 1) n_ones++;
    }

    if (B[0] == 0) {
        printf("%d\n", n_ones * 2);
    } else {
        printf("%d\n", n_ones * 2 - 1);
    }
}
