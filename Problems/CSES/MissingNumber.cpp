#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;
    vector<int> v(N - 1);
    for (int i = 0; i < N - 1; i++) cin >> v[i];
    sort(v.begin(), v.end());

    for (int i = 0; i < N; i++) {
        if (v[i] != i + 1) {
            cout << i + 1 << endl;
            return 0;
        }
    }
}