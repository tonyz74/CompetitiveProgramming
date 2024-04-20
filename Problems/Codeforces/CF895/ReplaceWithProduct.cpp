#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_array(string prefix, vector<long long>& arr) {
    printf("%s: ", prefix.c_str());
    for (int i = 0; i < arr.size(); i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");
}

void solve() {
    int N;
    cin >> N;

    vector<long long> a(N, 0);
    
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    if (N == 1) {
        printf("1 1\n");
        return;
    }

    // remove leading and trailing ones
    int real_start = 0;
    while (a[real_start] == 1) {
        real_start++;

        // whole thing is 1
        if (real_start == a.size()) {
            printf("1 1\n");
            return;
        }
    }

    int end_offset = 0;
    while (a[a.size() - end_offset - 1] == 1) {
        end_offset++;
    }

    int start_offset = real_start;
    a = vector<long long>(a.begin() + real_start, a.end() - end_offset);

    vector<long long> prefix_sum(a.size() + 1, 0);
    vector<long long> positions;
    positions.reserve(a.size() + 2);

    int num_nonone = 0;
    unsigned long long prod = 1;

    for (int i = 0; i < a.size(); i++) {
        prefix_sum[i + 1] = prefix_sum[i] + a[i];

        if (a[i] != 1) {
            positions.push_back(i);
            num_nonone++;
            prod *= a[i];

            if (num_nonone >= 40 || prod >= 1e9) {
                printf("%d %d\n", start_offset + 1, start_offset + (int) a.size());
                return;
            }
        }
    }

    // print_array("a", a);
    // print_array("prefix sum", prefix_sum);
    // print_array("positions", positions);

    long long total = -1;
    int best_l = -1, best_r = -1;

    for (int i = 0; i < positions.size(); i++) {
        int l = positions[i];
        long long prefix_left = prefix_sum[l];
        long long mult = 1;

        for (int j = i; j < positions.size(); j++) {
            int r = positions[j];
            long long prefix_right = prefix_sum[a.size()] - prefix_sum[r + 1];

            mult *= a[r];

            long long mine = prefix_left + prefix_right + mult;
            if (mine > total) {
                total = mine;
                best_l = l;
                best_r = r;
            }

            // printf("\n%d to %d:\n", l, r);
            // printf("pl: %lld, pr: %lld, mult: %lld\n", prefix_left, prefix_right, mult);
            // printf("val = %lld\n", prefix_left + prefix_right + mult);
        }
    }
    
    printf("%d %d\n", start_offset + best_l + 1, start_offset + best_r + 1);
}

int main(void) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}