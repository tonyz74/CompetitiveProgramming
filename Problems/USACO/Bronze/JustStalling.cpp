#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

int n_lteq(const vector<i64>& vec, i64 val) {
    int x = 0;
    for (int i = 0; i < (int) vec.size(); i++) {
        if (vec[i] <= val) x++;
    }

    return x;
}

int main(void) {
    int N; cin >> N;

    vector<i64> heights(N);
    vector<i64> limits(N);

    for (int i = 0; i < N; i++) cin >> heights[i];
    for (int i = 0; i < N; i++) cin >> limits[i];

    std::sort(heights.begin(), heights.end());
    std::sort(limits.begin(), limits.end());

    i64 combis = n_lteq(heights, limits[0]);
    for (int i = 1; i < N; i++) {
        combis *= n_lteq(heights, limits[i]) - i; 
    }

    cout << combis << endl;
}