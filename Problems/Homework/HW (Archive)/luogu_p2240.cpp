#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main(void) {
    int N, T;
    cin >> N;
    cin >> T;

    vector<pair<int, int> > piles(N);

    for (int i = 0; i < N; i++) {
        int m, v;
        cin >> m >> v;
        
        piles[i] = make_pair(m, v);
    }

    // get price per unit weight
    vector<pair<float, int> > prices(N);

    for (int i = 0; i < N; i++) {
        float ratio = piles[i].second / (float) piles[i].first;
        prices[i] = make_pair(ratio, piles[i].first);
    }

    sort(prices.begin(), prices.end());

    float value = 0.0;
    int weight = 0;
    int idx = prices.size() - 1;

    while (weight < T && idx >= 0) {
        int to_take = min(T - weight, prices[idx].second);
        weight += to_take;
        value += (float) to_take * prices[idx].first;
        idx--;
    }

    printf("%.2f\n", value);
}
