#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

struct point {
    int x, y;

    bool operator<(const point& rhs) const {
        return make_pair(x, y) < make_pair(rhs.x, rhs.y);
    }
};

#define OFFSET 600

int nhoj_cows[2048][2048];
int added_cows[2048][2048];

int exists(point p) {
    return (nhoj_cows[p.x][p.y] || added_cows[p.x][p.y]);
}

int count_neighbors(point p) {
    point adj[] = {
        { p.x + 1, p.y },
        { p.x - 1, p.y },
        { p.x, p.y + 1 },
        { p.x, p.y - 1 },
    };

    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        if (exists(adj[i])) cnt++;
    }

    return cnt;
}

int main(void) {
    
    int N;
    cin >> N;

    int n_added = 0;

    for (int i = 0; i < N; i++) {
        point p;
        cin >> p.x >> p.y;
        p.x += OFFSET;
        p.y += OFFSET;

        nhoj_cows[p.x][p.y] = true;

        if (added_cows[p.x][p.y]) {
            added_cows[p.x][p.y] = false;
            n_added--;
            printf("%d\n", n_added);
            continue;
        }

        deque<point> to_fill;
        to_fill.push_back(p);

        while (!to_fill.empty()) {
            point top = to_fill.front();
            to_fill.pop_front();

            point surround[] = {
                { top.x + 1, top.y },
                { top.x - 1, top.y },
                { top.x, top.y + 1 },
                { top.x, top.y - 1 },
            };
            int nonexistent = -1;

            for (int j = 0; j < 4; j++) {
                point pt = surround[j];
                if (exists(pt)) {
                    if (count_neighbors(pt) == 3) {
                        to_fill.push_back(pt);
                    }
                } else {
                    nonexistent = j;
                }
            }

            if (count_neighbors(top) == 3) {
                point new_p = surround[nonexistent];
                added_cows[new_p.x][new_p.y] = true;
                n_added++;
                to_fill.push_back(new_p);
            }
        }

        printf("%d\n", (int) n_added);
    }
}