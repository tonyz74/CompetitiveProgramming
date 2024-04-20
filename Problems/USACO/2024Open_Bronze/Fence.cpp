#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using i64 = long long;

int N, P;

void get_ordered_posts() {
    unordered_map<int, vector<pair<int, int> > > same_x;
    unordered_map<int, vector<pair<int, int> > > same_y;

    vector<pair<int, int> > unordered_posts(P + 1);
    for (int i = 1; i <= P; i++) {
        int x, y; cin >> x >> y;
        unordered_posts[i].first = x;
        unordered_posts[i].second = y;

        same_x[x].push_back(make_pair(y, i));
        same_y[y].push_back(make_pair(x, i));
    } 

    for (auto p: same_x) {
        std::sort(same_x[p.first].begin(), same_x[p.first].end());
    }
    for (auto p: same_y) {
        std::sort(same_y[p.first].begin(), same_y[p.first].end());
    }

    vector<vector<int> > graph(P + 1);
    for (int i = 1; i <= P; i++) {
        pair<int, int> p = unordered_posts[i];
        int x = p.first;
        int y = p.second;

        int pos_y = std::lower_bound(same_x[x].begin(), same_x[x].end(), make_pair(y, 0)) - same_x[x].begin();
        int n_above = same_x[x].size() - (pos_y + 1);
        int n_below = pos_y;

        if (n_above % 2 == n_below % 2) {
            printf("-1\n");
            exit(0);
        }

        if (n_above % 2 == 1) {
            graph[i].push_back(same_x[x][pos_y + 1].second);
            // printf("connect %d to %d (same x), above\n", i, same_x[x][pos_y + 1].second);
        } else if (n_below % 2 == 1) {
            graph[i].push_back(same_x[x][pos_y - 1].second);
            // printf("connect %d to %d (same x), below\n", i, same_x[x][pos_y - 1].second);
        }

        int pos_x = std::lower_bound(same_y[y].begin(), same_y[y].end(), make_pair(x, 0)) - same_y[y].begin();
        int n_right = same_y[y].size() - (pos_x + 1);
        int n_left = pos_x;

        if (n_right % 2 == n_left % 2) {
            printf("-1\n");
            exit(0);
        }

        if (n_right % 2 == 1) {
            graph[i].push_back(same_y[y][pos_x + 1].second);
            // printf("connect %d to %d (same y), right\n", i, same_y[y][pos_x + 1].second);
        } else if (n_left % 2 == 1) {
            graph[i].push_back(same_y[y][pos_x - 1].second);
            // printf("connect %d to %d (same y), left\n", i, same_y[y][pos_x - 1].second);
        }
    }

    int start = 1;
    vector<int> seen(P + 1, 0);

    vector<pair<int, int> > points(1);

    while (!seen[start]) {
        seen[start] = true;
        points.push_back(unordered_posts[start]);

        int next = -1;
        for (int x: graph[start]) {
            if (!seen[x]) {
                next = x; break;
            }
        }

        if (next == -1) break;
        start = next;
    } 

    for (int i = 1; i <= P; i++) {
        printf("%d %d\n", points[i].first, points[i].second);
    }
}

int main(void) {
    cin >> N >> P;
    get_ordered_posts();
}