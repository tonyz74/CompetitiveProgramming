#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

enum op {
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
};

using namespace std;

int max_val = -1e9;

int evaluate(int a, int b, op o, bool& ok) {
    if (o == ADD) return a + b;
    else if (o == SUB) return a - b;
    else if (o == MUL) return a * b;
    else if (o == DIV) {
        if (b == 0 || a % b) {
            ok = false;
            return -1e9;
        }
        return a / b;
    }

    return -1e9;
}

void search(vector<int> nums, vector<op> ops) {
    if (nums.size() == 1 && nums[0] <= 24) {
        max_val = max(max_val, nums[0]);
        return;
    }

    for (int selected_op = 0; selected_op < (int) ops.size(); selected_op++) {
        // pick this one?
        vector<int> new_nums;
        vector<op> new_ops;

        for (int i = 0; i < (int) nums.size(); i++) {
            int ans = nums[i];
            if (i == selected_op) {
                bool is_ok = true;
                ans = evaluate(nums[i], nums[i + 1], ops[i], is_ok);
                if (!is_ok) return;

                i++;
            }
            
            if (i < (int) ops.size()) {
                new_ops.push_back(ops[i]);
            }

            new_nums.push_back(ans);
        }

        // printf("searching another\n");
        search(new_nums, new_ops);
    }
}

int main(void) {
    int N; cin >> N;

    for (int n = 0; n < N; n++) {
        max_val = -1e9;

        vector<int> xyzw(4);
        for (int k = 0; k < 4; k++) cin >> xyzw[k];
        sort(xyzw.begin(), xyzw.end());

        // pick all possible ops
        vector<op> operations;
        for (int t = ADD; t <= DIV; t++) {
            for (int k = 0; k < 3; k++) operations.push_back((op) t);
        }

        do {
            do {
                vector<op> ops = { operations[0], operations[1], operations[2] };
                search(xyzw, ops);
                std::reverse(operations.begin() + 3, operations.end());
            } while (next_permutation(operations.begin(), operations.end()));
        } while (next_permutation(xyzw.begin(), xyzw.end()));

        cout << max_val << endl;
    }
}