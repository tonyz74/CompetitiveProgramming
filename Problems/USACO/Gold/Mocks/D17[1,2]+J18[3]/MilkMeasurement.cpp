#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define HERD_CNT ((int) (2 * 1e9))

using namespace std;

struct rec {
    int time;
    int cow;
    int delta;

    rec() {}
    rec(int t, int c, int d): time(t), cow(c), delta(d) {
    }

    bool operator<(const rec& rhs) const {
        return time < rhs.time;
    }
};

int main(void) {
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    int N, G;
    cin >> N >> G;

    vector<rec> recs(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> recs[i].time >> recs[i].cow >> recs[i].delta;
    }
    std::sort(recs.begin() + 1, recs.end());

    map<int, int> amt_with_score;
    map<int, int> score_of;

    amt_with_score[G] = HERD_CNT;
    int n_changes = 0;
    int prev_max_score = G;

    for (int i = 1; i <= N; i++) {
        // printf("\nevent: %d, cow %d changes %d\n", recs[i].time, recs[i].cow, recs[i].delta);
        int prev_amt = amt_with_score[prev_max_score];

        auto fnd = score_of.find(recs[i].cow);
        if (fnd == score_of.end()) {
            score_of[recs[i].cow] = G;
            fnd = score_of.find(recs[i].cow);
        }

        int old_score = fnd->second;
        int new_score = old_score + recs[i].delta;
        amt_with_score[old_score]--;
        amt_with_score[new_score]++;

        if (amt_with_score[old_score] == 0) {
            amt_with_score.erase(old_score);
        }
        score_of[recs[i].cow] = new_score;

        int now_max_score = amt_with_score.rbegin()->first;
        int now_amt = (amt_with_score.rbegin()->second);

        // printf("now max: %d, now amt: %d\n", now_max_score, now_amt);

        if (prev_max_score == now_max_score) {
            if (prev_amt != now_amt) {
                // printf("increase: max has changed\n");
                n_changes++;
            }
        } else {
            // score has changed, could just be the max cow moving around though

            // only acceptable score change:
            // if i used to hold the max, and i now still hold the max,
            // and it is still only me in the max position, nothing changes
            if (old_score == prev_max_score &&
                new_score == now_max_score &&
                prev_amt == 1 && now_amt == 1) {
            } else {
                // printf("increase: new person became max\n");
                n_changes++;
            }
        }

        prev_max_score = now_max_score;
    }

    cout << n_changes << endl;
}