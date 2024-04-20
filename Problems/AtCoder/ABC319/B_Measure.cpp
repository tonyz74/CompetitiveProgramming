#include <vector>
#include <iostream>

typedef long long ll;
using namespace std;

int main(void) {
    int N;
    cin >> N;

    for (int i = 0; i <= N; i++) {
        int best = -1;

        for (int d = 1; d <= 9; d++) {
            if (N % d == 0 && i % (N / d) == 0) {
                best = d;
                break;
            }
        }

        if (best == -1) {
            cout << "-";
        } else {
            cout << best;
        }
    }
    cout << endl;
}