#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <set>

using namespace std;

struct layer {
    layer() {}
    layer(int sz, int ty): size(sz), type(ty) {}

    int size;
    int type;
};

struct test_tube {
    vector<layer> layers;
    int name;
    int n_ty[3];

    test_tube() {
        n_ty[0] = 0;
        n_ty[1] = 0;
        n_ty[2] = 0;
    }
};

void tt_add(test_tube& tt, layer L) {
    if (tt.layers.empty() || tt.layers.back().type != L.type) {
        tt.n_ty[L.type]++;
        tt.layers.push_back(L);
    } else {
        tt.layers.back().size += L.size;
    }
}

test_tube read_tt() {
    test_tube res;
    string s; cin >> s;

    int sz = s.size();
    for (int i = 0; i < sz; i++) {
        tt_add(res, layer(1, s[i] - '0'));
    }

    return res;
}

layer tt_pop(test_tube& tt) {
    assert(!tt.layers.empty());
    layer L = tt.layers.back();
    tt.n_ty[L.type]--;
    tt.layers.pop_back();
    return L;
}

void tt_pour(test_tube& src, test_tube& dst, int show) {
    if (show) {
        printf("%d %d\n", src.name, dst.name);
    }

    assert(!src.layers.empty());
    tt_add(dst, tt_pop(src));
}

void print_tt(const test_tube& tt) {
    for (int i = 0; i < (int) tt.layers.size(); i++) {
        printf("[%dx]%d ", tt.layers[i].type, tt.layers[i].size);
    }
}

// give all `to_give_F` to F, the others in S
int solve_with(test_tube F, test_tube S, int to_give_F, int show) {
    // printf("\nsolving with: %d\n", to_give_F);
    int ops = 0;

    test_tube B; B.name = 3;
    // the type to put into beaker
    int bk = (to_give_F == 1) ? 2 : 1;

    while (true) {
        if (!F.layers.empty() && F.layers.back().type == bk) {
            ops++;
            // printf("e\n");
            tt_pour(F, B, show);
        }
        if (!S.layers.empty() && S.layers.back().type == bk) {
            ops++;
            // printf("d\n");
            tt_pour(S, B, show);
        }

        // now all to_give_Fs at the tops, if this is true move all to F
        // only if there's only the same stuff, otherwise transfer to S
        if (F.n_ty[bk] == 0 && S.n_ty[to_give_F] != 0) {
            ops++;
            // printf("a\n");
            tt_pour(S, F, show);
        } else if (F.n_ty[to_give_F] != 0) {
            ops++;
            // printf("b\n");
            tt_pour(F, S, show);
            // printf("done b\n");
        }

        // beaker is non empty, S is missing some
        if (S.n_ty[to_give_F] == 0 && B.n_ty[bk] != 0) {
            // printf("c\n");
            ops++;
            tt_pour(B, S, show);
        }

        // F doesn't have 1s, S doesn't have 2s, beaker is empty
        if (F.n_ty[bk] == 0 && S.n_ty[to_give_F] == 0 && B.n_ty[bk] == 0) {
            break;
        }
    } 

    return ops;
}

void solve() {
    int N, P; cin >> N >> P;
    test_tube F = read_tt();
    test_tube S = read_tt();
    F.name = 1;
    S.name = 2;

    if (F.layers.size() == 1 && S.layers.size() == 1) {
        printf("0\n");
        return;
    }
    // print_tt(F); printf("\n");
    // print_tt(S); printf("\n");

    vector<pair<int, int> > answers;
    answers.push_back(make_pair(solve_with(F, S, 1, 0), 1));
    answers.push_back(make_pair(solve_with(F, S, 2, 0), 2));
    answers.push_back(make_pair(solve_with(S, F, 2, 0), 3));
    answers.push_back(make_pair(solve_with(S, F, 1, 0), 4));

    std::sort(answers.begin(), answers.end());
    printf("%d\n", answers[0].first);
    if (P == 2 || P == 3) {
        if (answers[0].second == 1) {
            solve_with(F, S, 1, 1);
        } else if (answers[0].second == 2) {
            solve_with(F, S, 2, 1);
        } else if (answers[0].second == 3) {
            solve_with(S, F, 2, 1);
        } else {
            solve_with(S, F, 1, 1);
        }
    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}
