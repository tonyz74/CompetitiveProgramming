#include <iostream>
#include <vector>
#include <string>

using namespace std;

int compute(const vector<int> &groups) {
    if ((int) groups.size() == 0) return 0;

    int max_day = 1e9;

    for (int g: groups) {
        int my_max = g / 2;
        if (g % 2 == 0) my_max--;

        max_day = min(max_day, my_max);
    }

    int n_cows = 0;
    for (int g: groups) {
        // how many cows to fill this in max_day days?
        int block = 2 * max_day + 1;
        int div = g / block;
        if (g % block != 0) div++;

        n_cows += div;
    }

    return n_cows;
}

int main(void) {
    int N; cin >> N;
    string state; cin >> state;

    vector<int> groups;

    int leading_group = 0;
    int i = 0;
    while (state[i] == '1') {
        leading_group++;
        i++;
    }

    int current_group = 0;
    for (int j = i; j < N; j++) {
        char c = state[j];

        if (c == '0') {
            if (current_group) groups.push_back(current_group);
            current_group = 0;
        } else {
            current_group++;
        }
    }

    int trailing_group = current_group;

    // i'm not sure if giving the option to add to the back is always
    // a good thing, so I'll compute for the four permutations
    vector<pair<int, int> > offsets = {
        {1, 1},
        {0, 0},
        {1, 0},
        {0, 1}
    };

    int max_day_back = 1e9;
    int max_day_front = 1e9;

    if (leading_group) {
        max_day_front = leading_group - 1;
    }
    if (trailing_group) {
        max_day_back = trailing_group - 1;
    }

    int max_day = min(max_day_back, max_day_front);

    for (int g: groups) {
        int my_max = g / 2;
        if (g % 2 == 0) my_max--;

        max_day = min(max_day, my_max);
    }

    int n_cows = 0;
    int block = 2 * max_day + 1;

    for (int g: groups) {
        // how many cows to fill this in max_day days?
        int div = g / block;
        if (g % block != 0) div++;

        n_cows += div;
    }

    int specials[] = {leading_group, trailing_group};
    for (int x: specials) {
        if (x) {
            if (block >= x) n_cows++; 
            else {
                int div = x / block;
                if (x % block != 0) div++;
                n_cows += div;
            }
        }
    }

    cout << n_cows << endl;
}