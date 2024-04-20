#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void setIO() {
    freopen("mixmilk.in", "r", stdin);
    freopen("mixmilk.out", "w,", stdout);
}

int main(void) {
    setIO();

    ll C[4] = {0};
    ll M[4] = {0};
    cin >> C[1] >> M[1] >> C[2] >> M[2] >> C[3] >> M[3];

    int target = 2;
    for (int iter = 1; iter <= 100; iter++) {
        int me = (target == 1) ? 3 : target - 1;

        // pour max possible into target
        ll amt_poured = 0;
        ll amt_exceeded = M[me] + M[target] - C[target];
        if (amt_exceeded > 0) {
            amt_poured = M[me] - amt_exceeded;
        } else {
            amt_poured = M[me];
        }

        M[me] -= amt_poured;
        M[target] += amt_poured;

        target++;
        if (target == 4) target = 1;
    }

    cout << M[1] << endl << M[2] << endl << M[3] << endl;
}