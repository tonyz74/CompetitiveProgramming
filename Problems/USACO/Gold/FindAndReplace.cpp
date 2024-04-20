#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cassert>

using namespace std;

bool validate(const string& in, const string& out) {
    set<char> unq_out;
    for (char c: out) {
        unq_out.insert(c);
    }
    if ((int) unq_out.size() == 52 && in != out) {
        return false;
    }

    map<char, char> io;
    for (int x = 0; x < (int) in.size(); x++) {
        if (!io.count(in[x])) {
            io[in[x]] = out[x];
        }

        if (io[in[x]] != out[x]) {
            return false;
        }
    }

    return true;
}

int node_id(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 26;
    }

    printf("FAILED AT CHARACTER %c (%d)\n", c, (int) c);
    exit(-5);
}

void solve() {
    string input;
    string output;

    cin >> input >> output;

    // validate first
    if (!validate(input, output)) {
        printf("-1\n");
        return;
    }

    // now compute: total edges + num cycles
    // do this through topological sort, everything remaining
    /// will be within a cycle, which we can do the iterate/remove on

    // create the DAG: X -> Y means want to transform character X to character Y
    vector<bool> exists(52);
    vector<int> graph(52, -1);
    vector<set<int> > reverse_graph(52);

    vector<int> indegree(52);

    int base_edges = 0;

    for (int i = 0; i < (int) input.size(); i++) {
        int in = node_id(input[i]);
        int corresponding = node_id(output[i]);
        assert(corresponding != -1);

        if (in == corresponding) continue;

        if (graph[in] == -1) {
            graph[in] = corresponding;
            reverse_graph[corresponding].insert(in);

            exists[in] = true;
            exists[corresponding] = true;

            indegree[corresponding]++;

            base_edges++;
        }
    }

    vector<int> frontier;
    for (int i = 0; i < 52; i++) {
        if (exists[i] && indegree[i] == 0) {
            frontier.push_back(i);
        }
    }

    while (!frontier.empty()) {
        vector<int> new_front;

        for (int i = 0; i < (int) frontier.size(); i++) {
            int conn = graph[frontier[i]];
            if (conn == -1) continue;
            indegree[conn]--;

            if (indegree[conn] == 0) {
                new_front.push_back(conn);
            }
        }

        frontier = new_front;
    }

    // start removing cycles
    set<int> possible_cycle;
    for (int i = 0; i < 52; i++) {
        if (indegree[i] != 0) {
            possible_cycle.insert(i);
        }
    }

    int n_cycles = 0;
    // printf("base: %d\n", base_edges);

    while (!possible_cycle.empty()) {
        int top = *possible_cycle.begin();
        int orig = top;

        vector<int> cycle;

        while (true) {
            cycle.push_back(top);
            top = graph[top];

            if (top == orig) break;
        }

        bool within_larger = false;
        for (int x: cycle) {
            possible_cycle.erase(x);

            // if there's another edge except
            // the cycle edge, there's a way to
            // easily untangle the cycle
            if (reverse_graph[x].size() >= 2) {
                within_larger = true;
            }
        }

        if (!within_larger) n_cycles++;
    }

    printf("%d\n", base_edges + n_cycles);
}

int main(void) {
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        solve();
    }
}