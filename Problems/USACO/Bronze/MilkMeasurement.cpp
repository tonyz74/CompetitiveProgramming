#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

using namespace std;

int N;
vector<tuple<int, string, int> > logs;
map<string, int> values;

using namespace std;

int main(void) {
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);

    cin >> N;
    logs.resize(N);
    for (int i = 0; i < N; i++) {
        int t;
        string cow;
        int diff;
        cin >> t >> cow >> diff;

        logs[i] = make_tuple(t, cow, diff);
    }

    sort(logs.begin(), logs.end());

    int changed = 0;
    values["Bessie"] = 7;
    values["Elsie"] = 7;
    values["Mildred"] = 7;

    // map will be sorted by name
    vector<string> disp = { "Bessie", "Elsie", "Mildred" };

    for (int i = 0; i < N; i++) {
        values[get<1>(logs[i])] += get<2>(logs[i]);
        int max_output = max(values["Bessie"], max(values["Elsie"], values["Mildred"]));

        vector<string> new_disp;
        for (const auto &[name, output]: values) {
            if (output == max_output) {
                new_disp.push_back(name);
            }
        }

        // printf("time %d, new: %s, %s, %s\n", get<0>(logs[i]), new_disp[0].c_str(), new_disp[1].c_str(), new_disp[2].c_str());
        changed += (new_disp != disp);
        disp = new_disp;
    }

    cout << changed << endl;
}