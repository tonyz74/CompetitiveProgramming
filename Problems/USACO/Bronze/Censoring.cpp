#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

char out[2000000 + 8];

int main(void) {
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    string S, T;
    cin >> S >> T;

    int out_len = 0;

    for (char c: S) {
        out[out_len++] = c;

        if (out_len >= (int) T.length()) {
            int off = out_len - T.length();
            bool all = true;

            for (int i = 0; i < (int) T.length(); i++) {
                // cout << out[off + i];
                if (out[off + i] != T[i]) {
                    all = false;
                    break;
                }
            }

            if (all) {
                // printf("caught a moo\n");
                out_len -= T.length();
            }
        }
    }

    out[out_len] = 0;
    printf("%s\n", out);
}