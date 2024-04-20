#include <iostream>
#include <vector>
#include <set>

using namespace std;

int intersection(set<string> &a, set<string> &b) {
    int x = 0;
    for (string s: a) {
        if (b.count(s)) x++;
    }

    return x;
}

// in a but not in b.
set<string> excluded(set<string> &a, set<string> &b) {
    set<string> out;

    for (string s: a) {
        if (b.count(s) == 0) out.insert(s);
    }

    return out;
}

void print_state(const vector<set<string> > &leaves) {
    for (int i = 1; i < (int) leaves.size(); i++) {
        printf("[SS %d]: ", i);
        for (string s: leaves[i]) {
            printf("%s ", s.c_str());
        }
        printf("\n");
    } 
}

int main(void) {
    // freopen("evolution.in", "r", stdin);
    // freopen("evolution.out", "w", stdout);

    set<string> gained_traits;

    int N; cin >> N;
    vector<set<string> > leaves(N + 1);

    for (int i = 1; i <= N; i++) {
        int k; cin >> k;
        for (int j = 1; j <= k; j++) {
            string trait; cin >> trait;
            leaves[i].insert(trait);
        }
    }

    while (true) {
        int did_work = false;

        int lowest_lca = -1;
        pair<int, int> best_pair;

        for (int c1 = 1; c1 < (int) leaves.size(); c1++) {
            for (int c2 = c1 + 1; c2 < (int) leaves.size(); c2++) {
                int lca_depth = intersection(leaves[c1], leaves[c2]);

                if (lca_depth > lowest_lca) {
                    lowest_lca = lca_depth;

                    best_pair.first = c1;
                    best_pair.second = c2;
                }
            }
        }

        if (lowest_lca != -1) {
            print_state(leaves);
            printf("merging %d and %d\n", best_pair.first, best_pair.second);
        
            int to_erase = best_pair.first;
            int kept = best_pair.second;
            if (leaves[best_pair.second].size() > leaves[to_erase].size()) {
                to_erase = best_pair.second;
                kept = best_pair.first;
            }

            // gained_traits should only gain the traits we can't see anymore because
            // of merging. the merged result's traits should still be accessible,
            // as they still exist as a leaf, and will be used in the future.
            set<string> excl = excluded(leaves[to_erase], leaves[kept]);

            for (string trait: excl) {
                if (gained_traits.count(trait)) {
                    printf("encountered duplicate trait %s\n", trait.c_str());
                    printf("no\n");
                    return 0;
                }

                printf("inserting trait %s into excluded\n", trait.c_str());
                gained_traits.insert(trait);
            }

            leaves.erase(leaves.begin() + to_erase);
            did_work = true;
            printf("\n");
        }

        if (!did_work) break;
    }

    printf("yes\n");
}