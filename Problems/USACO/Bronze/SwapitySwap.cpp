#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;

int main(void) {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);

    int N, K;
    int a1, a2;
    int b1, b2;

    cin >> N >> K >> a1 >> a2 >> b1 >> b2;

    // vector<int> v = { 0, 1, 2, 3, 4, 5 };
    // std::reverse(v.begin() + 1, v.begin() + 3);

    // for (int i = 0; i < (int) v.size(); i++) {
    //     cout << v[i] << " ";
    // }
    // cout << endl;
    // return 0;

    vector<int> state(N + 1);
    for (int i = 1; i <= N; i++) state[i] = i;

    set<vector<int> > results;
    results.insert(state);

    while (true) {
        std::reverse(state.begin() + a1, state.begin() + a2 + 1);
        std::reverse(state.begin() + b1, state.begin() + b2 + 1);

        // printf("at %lu: ", results.size());
        // for (int i = 1; i <= N; i++) {
        //     printf("%d ", state[i]);
        // }
        // printf("\n");

        if (results.count(state) != 0) {
            break;
        }

        results.insert(state);
    }


    int mod = K % results.size();
    // printf("mod is %d, res size is %lu\n", mod, results.size());
    state = vector<int>(N + 1);
    for (int i = 1; i <= N; i++) state[i] = i;

    for (int i = 0; i < mod; i++) {
        std::reverse(state.begin() + a1, state.begin() + a2 + 1);
        std::reverse(state.begin() + b1, state.begin() + b2 + 1);
    }

    for (int i = 1; i <= N; i++) {
        cout << state[i] << endl;
    }
    // printf("mod: %d\n", mod);
}