#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;
const i64 MODULUS = 1e9 + 7;

int main(void) {
    i64 N; cin >> N;
    vector<i64> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    std::sort(a.begin(), a.end());

    vector<i64> new_a;

    while (a.size() > 1) {
        new_a.clear();

        i64 begin = 0;
        i64 second = 1;

        while (new_a.size() < a.size() - 1) {
            // printf("iter: %d, begin: %d, second: %d\n", (int) new_a.size(), begin, second);
            // add a new one
            if (a.size() != 2 && (second == N || a[begin] + a[second] > a[begin + 1] + a[begin + 2])) {
                begin++;
                second = begin + 1;
                // printf("chose to swap\n");
            }

            // printf("adding %d (%d + %d)\n", a[begin] + a[second], a[begin], a[second]);
            new_a.push_back((a[begin] + a[second]));

            second++;
        }
        a = new_a;
    }

    cout << a[0] % MODULUS << endl;
}