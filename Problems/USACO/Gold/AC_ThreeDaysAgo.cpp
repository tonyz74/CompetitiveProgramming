#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

long long state[1 << 10];

int main(void) {
    long long N;
    string S; cin >> S;
    N = S.size();
    S = string(1, '.') + S;

    state[0] = 1;

    int mask = 0;
    for (int x = 1; x <= N; x++) {
        char c = S[x];
        int digit = c - '0';
        mask ^= (1 << digit);
        state[mask]++;
    }

    long long ways = 0;
    for (int mask = 0; mask < (1 << 10); mask++) {
        ways += (state[mask] * (state[mask] - 1)) / 2;
    }

    cout << ways << endl;
}