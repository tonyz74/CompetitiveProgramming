#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int digits[10];

int main(void) {
    int N; cin >> N;
    string S; cin >> S;

    for (int i = 0; i < N; i++) {
        digits[S[i] - '0']++;
    }

    // for (int i = 0; i < 10; i++) {
        // cout << digits[i] << endl;
    // }
    // cout << endl;

    int n = 0;

    for (int i = 0; i < 1e7; i++) {
        int dup[10];
        memcpy(dup, digits, 10 * sizeof(int));

        long long sq = (long long) i * (long long) i;
        long long orig_sq = sq;
        // cout << "checking " << sq << endl;
        bool all = true;

        while (sq != 0) {
            int digit = sq % 10;
            sq /= 10;
            dup[digit]--;

            if (dup[digit] < 0) {
                all = false;
                break;
            }
        }

        if (all) {
            for (int d = 1; d < 10; d++) {
                if (dup[d] != 0) { all = false; break; }
            }
        }
        if (all) {
            // squares.push_back(orig_sq);
            n++;
        }
    }

    // sort(squares.begin(), squares.end());
    // for (int i = 0; i < squares.size(); i++) {
    //     cout << squares[i] << " ";
    // }
    // cout << endl;
    
    std::cout << n << endl;
}