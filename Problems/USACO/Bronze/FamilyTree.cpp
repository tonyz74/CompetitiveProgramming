#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<string, bool> seen;
vector<vector<string> > groups;

// undirected
map<string, vector<string> > links;

// directed (points to parent), unique
map<string, string> up_tree;
// directed (points to child), not unique
map<string, vector<string> > down_tree;

void dfs(string current) {
    if (seen[current]) return;
    seen[current] = true;

    groups.back().push_back(current);

    for (string conn: links[current]) {
        dfs(conn);
    }
}


void find_depths(string root, int depth, map<string, int>& output) {
    output[root] = depth;

    for (string S: down_tree[root]) {
        find_depths(S, depth + 1, output);
    }
}


// guaranteed that they are in the same tree
string find_lca(string cow1, string cow2, map<string, int> depths) {
    // we want cow 1 to be higher up in the tree
    if (depths[cow1] > depths[cow2]) {
        std::swap(cow1, cow2);
    }

    // match the depths
    while (depths[cow1] != depths[cow2]) {
        cow2 = up_tree[cow2];
    }

    // now, go up together
    while (cow1 != cow2) {
        cow1 = up_tree[cow1];
        cow2 = up_tree[cow2];
    }

    return cow1;
}

int main(void) {
    freopen("family.in", "r", stdin);
    freopen("family.out", "w", stdout);

    int N; cin >> N;
    string bessie, elsie; cin >> bessie >> elsie;

    set<string> nodes;

    for (int i = 0; i < N; i++) {
        string parent, child;
        cin >> parent >> child;

        links[parent].push_back(child);
        links[child].push_back(parent);
        
        up_tree[child] = parent;
        down_tree[parent].push_back(child);

        nodes.insert(parent);
        nodes.insert(child);
    } 

    for (string node: nodes) {
        if (seen[node] == true) continue;

        groups.push_back(vector<string>());
        dfs(node);
    }

    int bessie_group = -1;
    int elsie_group = -1;

    for (int i = 0; i < (int) groups.size(); i++) {
        for (string x: groups[i]) {
            if (x == bessie) bessie_group = i;
            else if (x == elsie) elsie_group = i;
        }
    }

    if (bessie_group == elsie_group && bessie_group != -1) {
        vector<string> group = groups[bessie_group];
        string root;

        for (string node: group) {
            if (!up_tree.count(node)) {
                // this is the root
                root = node;
                break;
            }
        }

        map<string, int> depths_from_root;
        find_depths(root, 0, depths_from_root);

        string lca = find_lca(bessie, elsie, depths_from_root);

        map<string, int> depths_from_lca;
        find_depths(lca, 0, depths_from_lca);

        int bessie_depth = depths_from_lca[bessie];
        int elsie_depth = depths_from_lca[elsie];

        if (bessie_depth == 1 && elsie_depth == 1) {

            printf("SIBLINGS\n");

        } else if (bessie_depth == 0 || elsie_depth == 0) {

            // direct descendant
            int gen_gap = abs(bessie_depth - elsie_depth);

            string base = (bessie_depth == 0) ? bessie : elsie;
            string descendant = (bessie_depth == 0) ? elsie : bessie;

            printf("%s is the ", base.c_str());

            while (gen_gap >= 3) {
                printf("great-");
                gen_gap--;
            }

            if (gen_gap == 2) {
                printf("grand-");
                gen_gap--;
            }

            printf("mother of %s\n", descendant.c_str());

        } else if (bessie_depth == 1 || elsie_depth == 1) {
            string aunt = (bessie_depth == 1) ? bessie : elsie;
            string niece = (bessie_depth == 1) ? elsie : bessie;

            int gen_gap = max(bessie_depth, elsie_depth);
            gen_gap--;

            printf("%s is the ", aunt.c_str());

            while (gen_gap >= 2) {
                printf("great-");
                gen_gap--;
            }

            printf("aunt of %s\n", niece.c_str());

        } else {
            printf("COUSINS\n");
        }
    } else {
        printf("NOT RELATED\n");
    }
}