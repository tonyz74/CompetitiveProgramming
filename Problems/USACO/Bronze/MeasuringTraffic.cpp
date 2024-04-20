#include <iostream>
#include <vector>

using namespace std;

enum road_type {
    HIGHWAY,
    ON_RAMP,
    OFF_RAMP
};

struct info {
    road_type ty;
    int small, big;
};

int main(void) {
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);

    int N; cin >> N;

    vector<info> data(N);
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        road_type rty = HIGHWAY;
        if (s == "on") rty = ON_RAMP;
        else if (s == "off") rty = OFF_RAMP;

        data[i].ty = rty;
        cin >> data[i].small >> data[i].big;
    }

    // merge consecutive highways
    vector<info> merged;
    for (int i = 0; i < N; i++) {
        int c_small = data[i].small;
        int c_big = data[i].big;
        if (i + 1 < N && data[i].ty == HIGHWAY && data[i + 1].ty == HIGHWAY) {
            c_small = max(data[i + 1].small, data[i].small);
            c_big = min(data[i + 1].big, data[i].big);

            c_small = max(c_small, 0);
            c_big = max(c_big, 0);
            i++;
        }

        merged.push_back(info { data[i].ty, c_small, c_big });
    }

    int M = merged.size();
    int ehw = -1;
    int lhw = -1;

    for (int i = 0; i < M; i++) {
        if (merged[i].ty == HIGHWAY && ehw == -1) {
            ehw = i;
        }

        if (merged[i].ty == HIGHWAY) {
            lhw = i;
        }
    }

    // find the last entering flow
    int ismall = merged[lhw].small, ibig = merged[lhw].big;
    for (int i = lhw; i >= 0; i--) {
        if (merged[i].ty == ON_RAMP) {
            ismall -= merged[i].big;
            ibig -= merged[i].small;
        } else if (merged[i].ty == OFF_RAMP) {
            ismall += merged[i].small;
            ibig += merged[i].big;
        } else if (merged[i].ty == HIGHWAY) {
            ismall = max(ismall, merged[i].small);
            ibig = min(ibig, merged[i].big);
        }

        // printf("ty = %d, new values: %d %d\n", merged[i].ty, ismall, ibig);

        ismall = max(ismall, 0);
        ibig = max(ibig, 0);
    }

    int fsmall = merged[ehw].small, fbig = merged[ehw].big;
    for (int i = ehw; i < M; i++) {
        if (merged[i].ty == ON_RAMP) {
            fsmall += merged[i].small;
            fbig += merged[i].big;
        } else if (merged[i].ty == OFF_RAMP) {
            fsmall -= merged[i].big;
            fbig -= merged[i].small;
        } else {
            // if the highway gave a more accurate measurement, accept it
            fsmall = max(fsmall, merged[i].small);
            fbig = min(fbig, merged[i].big);
        }

        fsmall = max(fsmall, 0);
        fbig = max(fbig, 0);
    }

    printf("%d %d\n", ismall, ibig);
    printf("%d %d\n", fsmall, fbig);
}
