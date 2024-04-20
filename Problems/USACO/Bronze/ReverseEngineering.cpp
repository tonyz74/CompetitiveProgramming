#include <iostream>
#include <map>
#include <vector>

using namespace std;

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

    vector<bool> passed(M, false);
    
    while (true) {
        int if_found = false;

        for (int chr = 0; chr < N; chr++) for (int rhs = 0; rhs <= 1; rhs++) for (int ret = 0; ret <= 1; ret++) {
            // try the if statement: if (b[var] == rhs) return output
            int consistent = true;
            int did_one = false;

            for (int tc = 0; tc < M; tc++) {
                if (passed[tc]) continue;

                if (inputs[tc][chr] == rhs) {
                    did_one = true;
                    if (outputs[tc] != ret) {
                        consistent = false;
                        break;
                    }
                }
            }

            // if it's consistent, but only because nothing was inspected, we skip
            if (consistent && did_one) {
                for (int tc = 0; tc < M; tc++) {
                    if (passed[tc]) continue;

                    // we know they're consistent now
                    if (inputs[tc][chr] == rhs) {
                        passed[tc] = true;
                    }
                }

                if_found = true;
                goto found;
            }
        }

        found: (void) 0;
        if (!if_found) break;
    }


    // no more further simplifying we can do. judge by current factors,
    // and if that works, success, otherwise Elsie must be lying
    int all_passed = true;
    for (int i = 0; i < M; i++) {
        if (passed[i] == false) {
            all_passed = false;
            break;
        }
    }

    if (all_passed) {
        printf("OK\n");
    } else {
        printf("LIE\n");
    }
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}