#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N, T; cin >> N >> T;

    vector<pair<i64, i64> > data;
    for (int i = 0; i < N; i++) {
        i64 d, b; cin >> d >> b;
        data.push_back(make_pair(d, b));
    }
    sort(data.begin(), data.end());

    // force it to process
    if (data.back().first != T) data.push_back(make_pair(T, 0));

    i64 n_eaten = 0;
    i64 haybale_stock = 0;

    for (int i = 0; i < (int) data.size(); i++) {
        if (i != 0) {
            i64 diff = data[i].first - data[i - 1].first;
            i64 ate = min(diff, haybale_stock);
            n_eaten += ate;
            haybale_stock -= ate;
        }

        haybale_stock += data[i].second;
    }

    // if we end on day T, with some haybales left over, +1
    if (data.back().first == T && haybale_stock != 0) {
        n_eaten++;
        haybale_stock--;
    }

    printf("%lld\n", n_eaten);
}