#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    vector<int> A(N + 1, 0);
    for (int i = 1; i < N + 1; i++) {
        cin >> A[i];
    }

    // 1 1 2 5 4
    // 1 2 5 4

    vector<int> DP(N + 1, 0);
    int best = 0;

    for (int i = 1; i < N + 1; i++) {
        if (A[i] <= i) {
            for (int k = 0; k < i; k++) {
                if (A[k] < A[i]) {
                    if (A[k] + (i - k) >= A[i]) {
                        DP[i] = max(DP[i], DP[k] + 1);
                    } else {
                        // cout << "did not pass for i: "
                        //     << i << ", k: " << k << ", "
                        //     << A[i] << ", " << A[k] << endl;
                        //     cout << (i - k) << ", " << A[k] + (i - k) << endl;
                    }
                }
            }    
        }
        best = max(best, DP[i]);
    }

    // cout << endl << endl;
    // for (const auto& i : A) {
    //     cout << i << " ";
    // }
    // cout << endl;
    // for (int i = 0; i < DP.size(); i++) {
    //     cout << DP[i] << " ";
    // }
    // cout << endl;

    cout << best << endl;
}
