#include <iostream>
#include <vector>

using namespace std;

struct tree {
    int n;
    vector<vector<int> > conn;
    vector<int> max_dist;
};

void find_dists(tree* t) {
    
}

tree read() {
    tree t;
    cin >> t.n;
    t.conn.resize(t.n + 1);
    for (int i = 0; i < t.n - 1; i++) {
        int s, e; cin >> s >> e;
        t.conn[s].push_back(e);
        t.conn[e].push_back(s);
    }

    find_dists(&t);
}

int main(void) {
}