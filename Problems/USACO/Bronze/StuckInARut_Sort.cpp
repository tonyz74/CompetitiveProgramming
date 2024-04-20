#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

struct cow {
    int sx, sy;
    int id;
};

int ecow_len = 0;
int ncow_len = 0;
cow ecows[59];
cow ncows[59];

bool closest_down(cow c1, cow c2) {
    return c1.sy < c2.sy;
}

bool closest_left(cow c1, cow c2) {
    return c1.sx < c2.sx;
}

int stopped_time[1024];

int main(void) {
    cin >> N;
    for (int i = 0; i < N; i++) {
        char c; cin >> c;
        int sx, sy; cin >> sx >> sy;

        if (c == 'E') {
            ecows[ecow_len++] = cow { .sx = sx, .sy = sy, .id = i };
        } else {
            ncows[ncow_len++] = cow { .sx = sx, .sy = sy, .id = i };
        }
    }

    sort(ecows, ecows + ecow_len, closest_down);
    sort(ncows, ncows + ncow_len, closest_left);

    int dist[1024];
    for (int i = 0; i < 1024; i++) dist[i] = -1;

    // use all the ecows to stop the ncows (or get stopped)
    for (int e = 0; e < ecow_len; e++) {
        for (int n = 0; n < ncow_len; n++) {
            // coordinates do not allow intersecting
            if (ncows[n].sx < ecows[e].sx || ncows[n].sy > ecows[e].sy) {
                continue;
            }

            int diff_x = (ncows[n].sx - ecows[e].sx);
            int diff_y = (ecows[e].sy - ncows[n].sy);

            // east cow will get stopped
            if (diff_x > diff_y && dist[ncows[n].id] == -1) {
                // printf("cow east cow %d stopped by north cow %d\n", ecows[e].id + 1, ncows[n].id + 1);
                dist[ecows[e].id] = diff_x;
                break;

            // north cow gets stopped (if hasn't already been stopped)
            } else if (diff_y > diff_x && dist[ncows[n].id] == -1) {
                // printf("cow east cow %d stopped north cow %d\n", ecows[e].id + 1, ncows[n].id + 1);
                dist[ncows[n].id] = diff_y;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (dist[i] == -1) cout << "Infinity" << '\n';
        else cout << dist[i] << '\n';
    }
}