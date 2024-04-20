#include <iostream>
#include <set>
#include <unordered_set>
#include <queue>

// important:
// ALWAYS TWO ADJACENT PARTICLES THAT INTERACT
// 1. consider parity of required y, it might change depending on if our particle
// i is an antimatter or regular matter one
// 2. when finding first element less than some element, dont just LB


using namespace std;
using i64 = long long;

struct collision {
    i64 x;
    i64 a, b;

    bool operator<(const collision& rhs) const {
        return x < rhs.x;
    }

    bool operator>(const collision& rhs) const {
        return x > rhs.x;
    }
};

void solve() {
    i64 N; cin >> N;
    vector<i64> P(N + 1);
    for (i64 i = 1; i <= N; i++) cin >> P[i];

    vector<i64> S(N + 1);
    for (i64 i = 1; i <= N; i++) cin >> S[i];

    // we know it's always adjacent particles that will hit
    vector<bool> already_hit(N + 1);

    auto find_ix = [&] (i64 i, i64 j) {
        i64 steps = (P[j] - P[i]) / (S[i] + S[j]);
        if ((P[j] - P[i]) % (S[i] + S[j])) {
            steps++;
        }


        if (i % 2 == 1) {
            return (steps - 1) * 2 + 1;
        } else {
            return 2 * steps;
        }
    };
    
    set<i64> particles;
    for (i64 i = 1; i <= N; i++) particles.insert(i);

    priority_queue<collision, vector<collision>, greater<collision> > hits;
    for (i64 i = 1; i <= N - 1; i++) {
        collision c;
        c.a = i;
        c.b = i + 1;
        c.x = find_ix(i, i + 1);
        hits.push(c);
    }

    vector<i64> ans(N + 1, 0);

    while (!hits.empty()) {
        collision next = hits.top();
        hits.pop();
        if (already_hit[next.a] || already_hit[next.b]) continue;
        already_hit[next.a] = true;
        already_hit[next.b] = true;

        ans[next.a] = next.x;
        ans[next.b] = next.x;

        // update surroundings
        auto at_a = particles.find(next.a);
        auto right_it = particles.lower_bound(next.b + 1);
        if (at_a == particles.begin() || right_it == particles.end()) continue;
        i64 left = *(--at_a);
        i64 right = *right_it;

        particles.erase(next.a);
        particles.erase(next.b);

        collision c;
        c.a = left;
        c.b = right;
        c.x = find_ix(left, right);
        hits.push(c);
    }

    for (i64 i = 1; i <= N; i++) {
        printf("%lld", ans[i]);
        if (i != N) printf(" ");
        else printf("\n");
    }

}

int main(void) {
    i64 T; cin >> T; while (T--) solve();
}