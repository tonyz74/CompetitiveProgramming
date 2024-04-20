#include <iostream>
#include <vector>
#include <string>

using namespace std;

int N, K;
vector<string> orig;
vector<vector<string> > items;


bool get_if_valid(int i, int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= N) return false;
    return items[i][r][c] == '#';
}

bool cmp_merge(int i1, int i2) {
    // printf("checking %d and %d\n", i1, i2);
    for (int sr1 = -N + 1; sr1 <= N - 1; sr1++) {
        for (int sc1 = -N + 1; sc1 <= N - 1; sc1++) {
            for (int sr2 = -N + 1; sr2 <= N - 1; sr2++) {
                for (int sc2 = -N + 1; sc2 <= N - 1; sc2++) {
                    bool good = true;


                    // we will exactly reconstruct orig at one point
                    for (int r = 0; good && r < N; r++) {
                        for (int c = 0; good && c < N; c++) {
                            int v1 = get_if_valid(i1, r + sr1, c + sc1);
                            int v2 = get_if_valid(i2, r + sr2, c + sc2);

                            if (v1 && v2) good = false;
                            else if ((v1 || v2) != (orig[r][c] == '#')) good = false;
                        }
                    }

                    if (good) return true;
                }
            }
        }
    }

    return false;
}

int main(void) {
    freopen("bcs.in", "r", stdin);
    freopen("bcs.out", "w", stdout);
    cin >> N >> K;

    for (int i = 0; i < N; i++) {
        string S; cin >> S;
        orig.push_back(S);
    }

    items.resize(K);
    for (int i = 0; i < K; i++) {
        for (int ln = 0; ln < N; ln++) {
            string S;
            cin >> S;

            items[i].push_back(S);
        }
    }

    for (int i = 0; i < K; i++) {
        for (int j = i + 1; j < K; j++) {
            if (cmp_merge(i, j)) {
                cout << i + 1 << " " << j + 1 << endl;
                return 0;
            }
        }
    } 
}
