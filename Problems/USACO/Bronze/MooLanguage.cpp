#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct store {
    int t1, t2;
    int J, L;
};

int min_all(const vector<int>& v) {
    int m = 1e9;
    for (int x: v) m = min(m, x);
    return m;
}

void solve() {
    // N words, C commas, P periods
    int N, C, P;
    cin >> N >> C >> P;

    vector<string> iverbs;
    vector<string> tverbs;
    vector<string> nouns;
    vector<string> conjs;

    for (int i = 0; i < N; i++) {
        string s, t; cin >> s >> t;
        if (t == "transitive-verb") {
            tverbs.push_back(s);
        } else if (t == "intransitive-verb") {
            iverbs.push_back(s);
        } else if (t == "noun") {
            nouns.push_back(s);
        } else if (t == "conjunction") {
            conjs.push_back(s);
        }
    }

    int best_wc = 0;
    store best {0,0,0,0};

    // iterate through the number of type-1 sentences
    for (int n_t1 = 0; n_t1 <= (int) iverbs.size(); n_t1++) {
        for (int n_t2 = 0; n_t2 <= (int) tverbs.size(); n_t2++) {
            // validate
            if (n_t1 + 2 * n_t2 > (int) nouns.size()) continue;

            int conjs_used = min((n_t1 + n_t2) / 2, (int) conjs.size());
            if (conjs_used + P < (n_t1 + n_t2)) continue;

            int listed_nouns = 0;
            if (n_t2 != 0) {
                listed_nouns = min((int) nouns.size() - n_t1 - 2 * n_t2, C);
            }
            // printf("at %d %d, listed nouns is %d\n", n_t1, n_t2, listed_nouns);

            int this_wc = n_t1 + 2 * n_t2 + conjs_used + listed_nouns + n_t1 + n_t2;
            if (this_wc > best_wc) {
                best.t1 = n_t1;
                best.t2 = n_t2;
                best.J = conjs_used;
                best.L = listed_nouns;
                best_wc = this_wc;
            }
        }
    }

    if (best_wc == 0) {
        cout << 0 << endl << endl;
    } else {
        cout << best_wc << endl;
        // printf(" (%d, %d, %d, %d)\n", best.t1, best.t2, best.J, best.L);

        // greedily make sentences
        int nn = 0, tv = 0, iv = 0, cnj = 0;
        int cnj_ty_counter = 0;

        // put all the type 1 sentences first.
        for (int i = 0; i < best.t1; i++) {
            cout << nouns[nn++] << " " << iverbs[iv++];

            if (best.t2 == 0 && i == best.t1 - 1) {
                cout << "." << endl;
                
            } else if (cnj < best.J && cnj_ty_counter % 2 == 0) {
                cout << " " << conjs[cnj++] << " ";
            } else {
                cout << ". ";
            }
            cnj_ty_counter++;
        }

        for (int i = 0; i < best.t2; i++) {

            cout << nouns[nn++] << " " << tverbs[tv++] << " ";
            cout << nouns[nn++];

            // if last iteration
            if (i == best.t2 - 1) {

                for (int k = 0; k < best.L; k++) {
                    cout << ", " << nouns[nn++];
                }
                cout << "." << endl;

            } else {
                // otherwise do as normal

                if (cnj < best.J && cnj_ty_counter % 2 == 0) {
                    cout << " " << conjs[cnj++] << " ";
                } else {
                    cout << ". ";
                }

                cnj_ty_counter++;
            }
        }
    }
}

int main(void) {
    int T; cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}
