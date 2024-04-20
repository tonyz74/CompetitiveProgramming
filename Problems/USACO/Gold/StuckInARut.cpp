#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct cow {
    int x, y;
    int id;
};

int N;
vector<cow> easts;
vector<cow> norths;

void read_input() {
    cin >> N;

    for (int i = 1; i <= N; i++) {
        char dir; cin >> dir;
        int x, y; cin >> x >> y;

        cow c;
        c.x = x;
        c.y = y;
        c.id = i;

        if (dir == 'E') {
            easts.push_back(c);
        } else {
            norths.push_back(c);
        }
    }
}

bool cmp_y(const cow& lhs, const cow& rhs) {
    return lhs.y < rhs.y;
}

bool cmp_x(const cow& lhs, const cow& rhs) {
    return lhs.x < rhs.x;
}

int main(void) {
    read_input();

    std::sort(easts.begin(), easts.end(), cmp_y);
    std::sort(norths.begin(), norths.end(), cmp_x);

    vector<int> stopping_order;
    vector<int> stopped_by(N + 1, -1);

    for (cow e_cow: easts) {
        for (cow n_cow: norths) {
            // they'd be stopped in at a lower y than my current e_cow's y
            // anyways, as it's in sorted order, so don't bother checking
            if (stopped_by[n_cow.id] != -1) continue;

            // sorry, physically cannot intersect with this one
            if (n_cow.x < e_cow.x || e_cow.y < n_cow.y) {
                continue;
            }
            
            // int ix_x = n_cow.x;
            // int ix_y = e_cow.y;

            int n_dist = e_cow.y - n_cow.y;
            int e_dist = n_cow.x - e_cow.x;

            // north stopped by east
            if (n_dist > e_dist) {
                stopped_by[n_cow.id] = e_cow.id;
                stopping_order.push_back(n_cow.id);
            } 

            // east stopped by north
            else if (n_dist < e_dist) {
                stopped_by[e_cow.id] = n_cow.id;
                stopping_order.push_back(e_cow.id);
                goto next_east;
            }
        }

        next_east: (void) 0;
    }

    vector<int> stoppages(N + 1, 0);

    for (int stopped: stopping_order) {
        // printf("cow %d\n", stopped);
        int val = stoppages[stopped] + 1;
        // printf("%d += %d\n", stopped_by[stopped], val);
        stoppages[stopped_by[stopped]] += val;
    }

    // for (int i = 0; i < (int) stopping_order.size(); i++) {
    //     printf("%d ", stopping_order[i]);
    // }
    // printf("\n");

    for (int i = 1; i <= N; i++) {
        printf("%d\n", stoppages[i]);
    }

}