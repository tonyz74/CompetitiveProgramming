#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {

    int N;
    cin >> N;

    vector<int> W(N + 1);
    vector<int> X(N + 1);
    for (int i = 1; i <= N; i++) cin >> W[i] >> X[i];

    int max_ppl = -1;

    for (int start_utc = 0; start_utc <= 23; start_utc++) {
        int people = 0;

        for (int base = 1; base <= N; base++) {
            int cvt = (start_utc + X[base]) % 24;
            if (cvt < 9 || cvt + 1 > 18) continue;
            people += W[base];
        }

        max_ppl = max(people, max_ppl);
    }

    cout << max_ppl << endl;
}