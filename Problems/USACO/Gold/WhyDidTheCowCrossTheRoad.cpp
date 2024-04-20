#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

using i64 = long long;

struct timespan {
    i64 begin, end;   

    bool operator<(const timespan& rhs) const {
        return make_pair(end, begin) < make_pair(rhs.end, rhs.begin);
    }
};

int main(void) {
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);

    int C, N; cin >> C >> N;

    multiset<i64> chickens;
    for (int i = 0; i < C; i++) {
        i64 c; cin >> c;
        chickens.insert(c);
    }

    vector<timespan> cows;
    for (int i = 0; i < N; i++) {
        timespan ts;
        cin >> ts.begin >> ts.end;
        cows.push_back(ts);
    }

    i64 paired = 0;

    // cows which give up fast have priority
    std::sort(cows.begin(), cows.end());
    for (timespan cow: cows) {
        auto chicken_pos = chickens.lower_bound(cow.begin);

        if (chicken_pos != chickens.end() && *chicken_pos <= cow.end) {
            paired++;
            chickens.erase(chicken_pos);
        }
    }

    printf("%lld\n", paired);
}