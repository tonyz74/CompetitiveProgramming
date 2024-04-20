#include <iostream>
#include <queue>
#include <vector>
#include <array>

typedef long long i64;

using namespace std;

i64 N;
i64 target;
vector<i64> H;
vector<vector<i64> > tree;
vector<i64> all_weights;

vector<array<i64, 3> > operations;

i64 find_total_weight(i64 this_node, i64 parent) {
    i64 sum = H[this_node];

    for (i64 conn: tree[this_node]) {
        if (conn == parent) {
            continue;
        }

        sum += find_total_weight(conn, this_node);
    }

    all_weights[this_node] = sum;
    return sum;
}

void search(i64 this_node, i64 parent) {
    // process the ones with too much first
    for (i64 conn: tree[this_node]) {
        if (conn == parent) continue;

        if (all_weights[conn] >= 0) {
            // print("all_weights %d is %d\n", conn, all_weights[conn]);
            search(conn, this_node);
        }
    }

    // second pass, now distribute to the ones with too little
    for (i64 conn: tree[this_node]) {
        if (conn == parent) continue;

        if (all_weights[conn] < 0) {

            i64 need = (-all_weights[conn]);
            H[this_node] -= need;
            // printf("[%d] giving %d to child %d\n", this_node, need, conn);
            H[conn] += need;
            operations.push_back({this_node, conn, need});

            search(conn, this_node);
        }
    }

    all_weights[this_node] = 0;

    // give all my extras to my parent
    if (parent != 0) {
        if (H[this_node] != 0) {
            operations.push_back({this_node, parent, H[this_node]});
        }
        // printf("[%d] giving %d to parent %d\n", this_node, H[this_node], parent);
        H[parent] += H[this_node];
        H[this_node] = 0;
    }
}

int main(void) {
    cin >> N;
    tree.resize(N + 1);
    H.resize(N + 1);

    all_weights.resize(N + 1);

    i64 csum = 0;
    for (i64 i = 1; i <= N; i++) {
        cin >> H[i];
        csum += H[i];
    }
    target = csum / N;

    for (i64 i = 1; i <= N; i++) {
        H[i] -= target;
    }

    for (i64 i = 0; i < N - 1; i++) {
        i64 src, dst;
        cin >> src >> dst;
        tree[src].push_back(dst);
        tree[dst].push_back(src);
    } 

    find_total_weight(1, 0);

    // since this is undirected, let's just blindly assume 1 to be the root
    search(1, 0);

    cout << operations.size() << endl;
    for (auto op: operations) {
        cout << op[0] << " " << op[1] << " " << op[2] << endl;
    }
}