#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

struct info {
    string name;
    vector<string> traits;
};

int main(void) {
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);

    int N; cin >> N;
    vector<info> infos(N);

    for (int i = 0; i < N; i++) {
        cin >> infos[i].name;
        int K; cin >> K;
        for (int j = 0; j < K; j++) {
            string trait; cin >> trait;
            infos[i].traits.push_back(trait);
        }
    }

    int most_qs = 0;
    for (int i = 0; i < N; i++) {
        string actual = infos[i].name;
        set<string> actual_traits;
        for (string t: infos[i].traits) actual_traits.insert(t);

        for (int other = 0; other < N; other++) {
            if (other == i) continue;

            set<string> common_traits;
            for (string t: infos[other].traits) {
                if (actual_traits.count(t) != 0) common_traits.insert(t);
            }

            if (common_traits.size() < actual_traits.size()) {
                most_qs = max(most_qs, (int) common_traits.size() + 1);
            }
        }
    }

    cout << most_qs << endl;
}