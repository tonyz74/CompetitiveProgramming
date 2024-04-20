#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N, Q; cin >> N >> Q;

    vector<string> expression(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> expression[i];
    }

    vector<int> prefix(N + 1, 0);
    vector<int> suffix(N + 1, 0);

    auto compute_prefix = [&] (const vector<string> &expression, vector<int>& prefix) {
        int last_or = 0;
        for (int i = 1; i <= N; i += 2) {
            if (i == 1) {
                prefix[i] = (expression[i] == "true");
                continue;
            }

            string op = expression[i - 1];
            if (op == "or") last_or = i;

            if (op == "or" && expression[i] == "true") {
                prefix[i] = true;
            } else if (op == "or" && expression[i] == "false") {
                prefix[i] = prefix[i - 2];
            } else if (op == "and") {
                // and true has no effect
                if (expression[i] == "true") {
                    prefix[i] = prefix[i - 2];
                } else {

                    if (last_or == 0) {
                        prefix[i] = false;
                    } else {
                        // that or became false, so take on the prev value
                        prefix[i] = prefix[last_or - 2];
                    }

                }
            }
        }
    };

    compute_prefix(expression, prefix);

    std::reverse(expression.begin() + 1, expression.end());
    compute_prefix(expression, suffix);
    std::reverse(suffix.begin() + 1, suffix.end());
    std::reverse(expression.begin() + 1, expression.end());

    for (int query = 1; query <= Q; query++) {
        int L, R; cin >> L >> R;
        string desired_str; cin >> desired_str;
        int desired = desired_str == "true";

        bool before = false;
        string op_before = "or";
        if (L != 1) {
            before = prefix[L - 2];
            op_before = expression[L - 1];
        }

        bool after = false;
        string op_after = "or";
        if (R != N) {
            after = suffix[R + 2];
            op_after = expression[R + 1];
        }

        int ok = false;

        for (int test_val = 0; test_val <= 1; test_val++) {
            cout << before << op_before << test_val << op_after << after << endl;

            int value = test_val;

            if (op_before == "and") {
                value &= before;
            }
            if (op_after == "and") {
                value &= after;
            }

            if (op_before == "or") {
                value |= before;
            }
            if (op_after == "or") {
                value |= after;
            }

            ok |= (value == desired);
        }

        (void) ok;

        // if (ok) printf("Y");
        // else printf("N");
    } 

    printf("\n");
}