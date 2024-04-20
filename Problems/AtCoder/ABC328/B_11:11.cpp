#include <iostream>

using namespace std;

bool is_ok(int req, int n) {
    while (n > 0) {
        int last_dig = n % 10;
        n /= 10;

        if (last_dig != req) return false;
    }

    return true;
}

int main(void) {
    int N; cin >> N;

    int n_reps = 0;
    for (int i = 1; i <= N; i++) {
        int D; cin >> D;

        if (i >= 10 && i % 11 != 0) {
            continue;
        }

        for (int j = 1; j <= D; j++) {
            // is a multiple of 11 within 100,
            // so last digit will be ok
            n_reps += is_ok(i % 10, j);
        }
    }

    cout << n_reps << endl;
}