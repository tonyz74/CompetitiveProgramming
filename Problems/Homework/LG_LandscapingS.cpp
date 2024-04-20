#include <iostream>
#include <queue>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N, X, Y, Z; cin >> N >> X >> Y >> Z;
    vector<i64> A(N + 1);
    vector<i64> B(N + 1);

    for (i64 i = 1; i <= N; i++) cin >> A[i] >> B[i];

    // should i have given it to somebody before?

    // undoing this operation (at pos p.second) will cost you p.first units
    vector<pair<i64, i64> > give_ops_before;

    // should i have taken it from somebody before?
    vector<pair<i64, i64> > take_ops_before;

    i64 ans = 0;

    for (i64 i = 1; i <= N; i++) {
        while (A[i] != B[i]) {

            // if i have too much
            if (A[i] > B[i]) {

                i64 best = 1e9;
                i64 best_pos = -1;

                if (!give_ops_before.empty()) {
                    for (int j = 0; j < (int) give_ops_before.size(); j++) {
                        i64 now = Z * (i - give_ops_before[j].second) - give_ops_before[j].first;
                        if (now < best) {
                            best = now;
                            best_pos = j;
                        }
                    }
                }

                // if giving it to the later one now is better
                // than just discarding, do it
                if (best_pos != -1 && best < Y) {
                    // printf("regret in give ops before, pos %lld val %lld\n", top, Z * (i - top) - X);
                    ans += best;
                    give_ops_before.erase(give_ops_before.begin() + best_pos);

                    // now if we undo this one, we'll have to 
                    take_ops_before.push_back(make_pair(best, i));

                } else {
                    take_ops_before.push_back(make_pair(Y, i));
                    ans += Y;
                }

                A[i]--;

            } else if (A[i] < B[i]) {

                i64 best = 1e9;
                i64 best_pos = -1;

                if (!take_ops_before.empty()) {
                    for (int j = 0; j < (int) take_ops_before.size(); j++) {
                        i64 now = Z * (i - take_ops_before[j].second) - take_ops_before[j].first;
                        if (now < best) {
                            best = now;
                            best_pos = j;
                        }
                    }
                }

                if (best_pos != -1 && best < X) {
                    ans += best;
                    take_ops_before.erase(take_ops_before.begin() + best_pos);
                    give_ops_before.push_back(make_pair(best, i));

                } else {
                    give_ops_before.push_back(make_pair(X, i));
                    ans += X;
                }

                A[i]++;
            }
        }
    }

    cout << ans << endl;
}