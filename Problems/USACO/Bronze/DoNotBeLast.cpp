#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    freopen("notlast.in", "r", stdin);
    freopen("notlast.out", "w", stdout);

    int N; cin >> N;
    map<string, int> cow_values;

    for (int i = 0; i < N; i++) {
        string cow; int milk;
        cin >> cow >> milk;
        cow_values[cow] += milk;
    }

    vector<pair<int, string> > ranking;
    for (pair<string, int> c: cow_values) {
        string name = c.first;
        int milk = c.second;

        ranking.push_back(make_pair(milk, name));
    }

    sort(ranking.begin(), ranking.end());
    int first_milk = ranking[0].first;
    int loc = 0;

    for (int i = 0; i < N; i++) {
        if (first_milk == ranking[i].first) continue;

        loc = i;
        break;
    }

    if (loc + 1 < (int) ranking.size() &&
        ranking[loc + 1].first == ranking[loc].first) {
        cout << "Tie" << endl;
    } else {
        cout << ranking[loc].second << endl; 
    }
}