#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

struct region {
    int L, R;
    bool value;
};

int main(void) {
    int N, Q; cin >> N >> Q; 

    vector<string> whole_expr(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> whole_expr[i];
    }

    int and_region_start = 1;
    vector<region> regions;
    vector<int> trues_before;
    vector<int> trues_after;

    for (int i = 2; i <= N; i += 2) {
        if (whole_expr[i] == "or") {
            bool expr = 1;

            // do something with the region
            if (and_region_start != -1) {
                region reg;
                reg.L = and_region_start;
                reg.R = i - 1;

                for (int j = reg.L; j <= reg.R; j++) {
                    if (j % 2 == 1) {
                        expr &= whole_expr[j] == "true";
                    }
                }

                reg.value = expr;

                regions.push_back(reg);

                if (reg.value) {
                    trues_before.push_back(reg.R);
                } else {
                    trues_after.push_back(reg.L);
                }
            }
            and_region_start = -1;
        } else if (whole_expr[i] == "and" && and_region_start == -1) {
            and_region_start = i - 1;
        }
    }

    for (auto p: regions) {
        printf("%d %d %d\n", p.L, p.R, p.value);
    }

    for (int query = 1; query <= Q; query++) {
        int L, R; string target_str;
        cin >> L >> R >> target_str;
        bool target = target_str == "true";

        for (int replace_with = 0; replace_with <= 1; replace_with++) {

        }
    }
}