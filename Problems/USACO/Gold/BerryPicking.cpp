#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int N, K;
vector<int> B;

multiset<int>::iterator get_back(multiset<int> &ms) {
    auto it = ms.end();
    it--;

    return it;
}

int earnings(int take) {
    multiset<int> supply;
    for (int i = 0; i < N; i++) {
        supply.insert(B[i]);
    }

    for (int elsie = 0; elsie < K / 2; elsie++) {
        auto back = get_back(supply);

        int val = *back;
        supply.erase(back);
        val -= take;

        if (val < 0) return false;

        supply.insert(val);
    }

    int total = 0;

    for (int bessie = 0; bessie < K / 2; bessie++) {
        auto back = get_back(supply);

        int val = *back;
        int gain = min(take, val);
        val -= gain;
        total += gain;

        supply.erase(back);
        supply.insert(val);
    }

    return total;
}

int main(void) {
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    cin >> N >> K;
    B.resize(N);

    int max_b = 0;
    for (int i = 0; i < N; i++) {
        cin >> B[i];
        max_b = max(max_b, B[i]);
    }

    int max_earnings = 0;
    for (int b = 1; b < max_b; b++) {
        max_earnings = max(max_earnings, earnings(b));
    }

    printf("%d\n", max_earnings);
}