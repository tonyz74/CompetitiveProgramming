#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(void) {
    freopen("citystate.in", "r", stdin);
    freopen("citystate.out", "w", stdout);

    int N; cin >> N;

    vector<pair<string, string> > city_states;
    map<string, vector<pair<string, string> > > prefix_matches;

    for (int i = 0; i < N; i++) {
        string city, state; cin >> city >> state;
        string pre = city.substr(0, 2);

        city_states.push_back(make_pair(city, state));
        prefix_matches[pre].push_back(make_pair(city, state));
    }

    long long all_matches = 0;

    for (pair<string, string> cs: city_states) {
        string my_city = cs.first;
        string my_state = cs.second;

        string my_pre = my_city.substr(0, 2);
        
        long long matches = 0;

        if (prefix_matches.count(my_state)) {
            for (auto match: prefix_matches[my_state]) {
                // can't be the same thing matching, must be from different states
                if (match.second == my_pre && !(my_pre == my_state)) {
                    // printf("%s (%s) and %s (%s)\n", cs.first.c_str(), cs.second.c_str(), match.first.c_str(), match.second.c_str());
                    matches++;
                }
            }
        }

        all_matches += matches;
    }

    cout << (all_matches / 2) << endl;
}