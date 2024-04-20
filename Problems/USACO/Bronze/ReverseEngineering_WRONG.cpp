#include <iostream>
#include <map>
#include <vector>

// why doesn't this work?

using namespace std;

struct stmt {
    int var, rhs, result;

    stmt() {}
    stmt(int v, int r, int res): var(v), rhs(r), result(res) {}
};

void solve() {
    int N, M; cin >> N >> M;

    vector<vector<int> > inputs(M);
    vector<int> outputs(M);

    for (int i = 0; i < M; i++) {
        string in;
        string out;
        cin >> in >> out;

        // printf("%s, %s\n", in.c_str(), out.c_str());

        for (char x: in) {
            inputs[i].push_back(x - '0');
        }
        outputs[i] = (int) (out[0] - '0');
    }

    map<pair<int, int>, bool> determinants;
    vector<stmt> statements;
    
    while (true) {
        int all_contradictory = true;

        for (int chr = 0; chr < N; chr++) {
            int given_zero = -1;
            int given_one = -1;

            for (int id = 0; id < M; id++) {
                // this is already known to work, don't consider here
                if (determinants[{chr, inputs[id][chr]}] == true) continue;

                if (inputs[id][chr] == 0) {
                    if (given_zero == -1) given_zero = outputs[id];
                    else if (given_zero != outputs[id]) {
                        given_zero = -2;
                    }
                } else {
                    if (given_one == -1) given_one = outputs[id];
                    else if (given_one != outputs[id]) {
                        given_one = -2;
                    }
                }
            } 

            if (given_zero >= 0 || given_one >= 0) {
                all_contradictory = false;

                // just set it right now
                if (given_zero >= 0) {
                    determinants[{chr, 0}] = true;
                    statements.push_back(stmt(chr, 0, given_zero));
                }
                if (given_one >= 0) {
                    determinants[{chr, 1}] = true;
                    statements.push_back(stmt(chr, 1, given_one));
                }
            }

            // printf("[chr = %d]: => %d, %d\n", chr, given_zero, given_one);
        }

        if (all_contradictory) break;
    }


    // no more further simplifying we can do. judge by current factors,
    // and if that works, success, otherwise Elsie must be lying
    // for (stmt s: statements) {
    //     printf("if b[%d] == %d: return %d\n", s.var, s.rhs, s.result);
    // }

    int else_case = -1;
    for (int i = 0; i < M; i++) {
        int expected_output = outputs[i];
        int actual_output = -1;

        for (stmt s: statements) {
            if (inputs[i][s.var] == s.rhs) {
                actual_output = s.result;
                break;
            }
        }

        if (actual_output == -1 && else_case == -1) {
            // humor them, set else case to the expected
            // this won't work if the elses are contradictory
            else_case = outputs[i];
        }

        if (actual_output == -1) actual_output = else_case;

        if (actual_output != expected_output) goto contradiction;
    }
    printf("OK\n");
    return;

    contradiction: (void) 0;
    printf("LIE\n");
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}