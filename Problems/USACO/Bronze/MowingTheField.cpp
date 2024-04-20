#include <iostream>
#include <vector>
#include <map>

using namespace std;

using p = pair<int, int>;

int main(void) {
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    int N; cin >> N;
    map<p, int> pos;

    int cx = 0, cy = 0;
    int max_x = 1e9;

    int time = 0;
    for (int i = 0; i < N; i++) {
        char dir; cin >> dir;
        int steps; cin >> steps;

        for (int st = 0; st < steps; st++) {
            time++;

            if (dir == 'N') cy += 1;
            else if (dir == 'S') cy -= 1;
            else if (dir == 'W') cx -= 1;
            else if (dir == 'E') cx += 1;

            p cpos = make_pair(cx, cy);
            if (pos[cpos]) {
                int last_time = pos[cpos];
                int time_diff = time - last_time;
                
                max_x = min(max_x, time_diff);
            }

            pos[cpos] = time;
        }
    }

    if (max_x != 1e9) {
        cout << max_x << endl;
    } else {
        cout << -1 << endl;
    }
}