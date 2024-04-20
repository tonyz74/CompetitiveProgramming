#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    vector<pair<int, int> > dates;
    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        dates.push_back(make_pair(a, b));
    }

    sort(dates.begin(), dates.end());

    int comps = 0;
    int current = 0;

    for (int i = 1; i < N; i++) {
        if (dates[i].first >= dates[current].second) {
            comps++;
            current = i;
        } else {
            if (dates[i].second < dates[current].second) {
                current = i;
            }
        }
    }


    cout << ++comps << endl;
}
