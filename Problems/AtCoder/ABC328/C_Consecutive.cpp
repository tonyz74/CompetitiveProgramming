#include <iostream>
#include <string>

using namespace std;

#define MAXN ((int) (3 * 1e5 + 123))

int csum[MAXN];

int main(void) {
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

    int tot = 0;
    // N can't happen anyways
    for (int cs_i = 2; cs_i <= N; cs_i++) {
        if (S[cs_i - 1] == S[cs_i - 2]) tot++;
        csum[cs_i] = tot;
    }

    for (int i = 1; i <= Q; i++) {
        int l, r; cin >> l >> r;
        printf("%d\n", csum[r] - csum[l]);
    }
}