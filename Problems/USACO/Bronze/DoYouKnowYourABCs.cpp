#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int values[7];

bool in_values(int val) {
    for (int i = 0; i < 7; i++) {
        if (values[i] == val) return true;
    }

    return false;
}

int main(void) {
    for (int i = 0; i < 7; i++) {
        cin >> values[i];
    }

    vector<int> res = {-1, -1, -1};

    for (int i1 = 0; i1 < 7; i1++) {
        for (int i2 = i1 + 1; i2 < 7; i2++) {
            for (int i3 = i2 + 1; i3 < 7; i3++) {

                int v1 = values[i1];
                int v2 = values[i2];
                int v3 = values[i3];

                vector<int> must_be_in = {
                    v1 + v2,
                    v2 + v3,
                    v1 + v3,

                    v1 + v2 + v3
                };

                for (int val: must_be_in) {
                    if (!in_values(val)) {
                        goto not_this;
                    }
                }

                res[0] = v1;
                res[1] = v2;
                res[2] = v3;

                not_this: (void) 0;
            }
        }
    }

    sort(res.begin(), res.end());
    printf("%d %d %d\n", res[0], res[1], res[2]);
}