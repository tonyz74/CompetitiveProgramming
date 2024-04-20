#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

#define MAX_T 105

int main(void) {
    freopen("badmilk.in", "r", stdin);
    freopen("badmilk.out", "w", stdout);

    int N, M, D, S; cin >> N >> M >> D >> S;

    vector<map<int, int> > drank(M + 1);
    vector<set<int> > milk_by_person(N + 1);
    vector<int> sick_time(N + 1, -1);

    for (int i = 0; i < D; i++) {
        int p, m, t; cin >> p >> m >> t;

        milk_by_person[p].insert(m);

        if (drank[m].count(p)) {
            // we want the earliest time they drank this milk
            drank[m][p] = min(drank[m][p], t);
        } else {
            drank[m][p] = t;
        }
    }

    for (int i = 0; i < S; i++) {
        int p, t; cin >> p >> t;
        sick_time[p] = t;
    }

    int worst_case = 0;
    for (int badmilk = 1; badmilk <= M; badmilk++) {
        int this_case = (int) drank[badmilk].size();

        for (auto &&[person, drink_time]: drank[badmilk]) {
            int tos = sick_time[person];

            // -1 means they weren't recorded to be sick, may get sick after
            if (tos != -1 && tos <= drink_time) {
                goto not_bad_milk;
            }
        }

        for (int p = 1; p <= N; p++) {
            if (sick_time[p] != -1 && milk_by_person[p].count(badmilk) == 0) {
                goto not_bad_milk;
            }
        }

        if (this_case > worst_case) {
            worst_case = this_case;
        }

        not_bad_milk: (void) 1;
    }

    cout << worst_case << endl;
}