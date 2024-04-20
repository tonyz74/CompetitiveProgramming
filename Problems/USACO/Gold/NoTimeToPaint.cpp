#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

#define char_id(x) ((x) - 'A')
#define MAX_ID 25

using namespace std;


int N, Q;
string S;

int opened[MAX_ID + 1];
vector<pair<int, int> > regions[MAX_ID + 1];
vector<int> char_locations[MAX_ID + 1];

int main(void) {
    // make string 1 indexed
    cin >> N >> Q >> S;

    for (int i = 0; i <= MAX_ID; i++) {
        opened[i] = -1;
    }

    for (int i = 0; i < N; i++) {
        int id = char_id(S[i]);
        char_locations[id].push_back(i);

        for (int darker = id + 1; darker <= MAX_ID; darker++) {
            if (opened[darker] != -1) {
                regions[darker].push_back(make_pair(opened[darker], i - 1));
                opened[darker] = -1;
            }
        }

        if (opened[id] == -1) {
            opened[id] = i;
        }
    } 

    // at pos N, everything must close
    for (int to_close = 0; to_close <= MAX_ID; to_close++) {
        if (opened[to_close] != -1) {
            regions[to_close].push_back(make_pair(opened[to_close], N - 1));
            opened[to_close] = -1;
        }
    }

    // fix regions to their minimum values
    for (int id = 0; id <= MAX_ID; id++) {
        if (regions[id].empty() == false) {
            // we're searching based on the next one's start
            // so we should only iterate up to the end - 1
            for (int j = 0; j < (int) regions[id].size() - 1; j++) {
                int next_start = regions[id][j + 1].first;

                // we know it exists in the set
                auto iter = std::lower_bound(
                    char_locations[id].begin(),
                    char_locations[id].end(),
                    next_start
                );
                assert(iter != char_locations[id].begin());
                assert(iter != char_locations[id].end());
                iter--;

                // we've found the first existing element less than the next
                // region's first element. this will be our endpoint.
                regions[id][j].second = *iter;
            }

            regions[id].back().second = char_locations[id].back();
        }
    }

    int original_ans = 0;
    for (char c = 'A'; c <= 'Z'; c++) {
        int id = char_id(c);
        original_ans += (int) regions[id].size();

        // if (!regions[id].empty()) {
        //     printf("%c: ", c);
        //     for (auto p: regions[id]) {
        //         printf("[%d, %d] ", p.first, p.second);
        //     }
        //     printf("\n");
        // }
    }

    while (Q--) {
        int ans = original_ans;
        int L, R; cin >> L >> R;
        L--; R--;

        for (int id = 0; id <= MAX_ID; id++) {
            // printf("char: %c\n", id + 'A');
            if (regions[id].empty()) continue;

            int left_idx = std::lower_bound(
                regions[id].begin(),
                regions[id].end(),
                make_pair(L, 0)
            ) - regions[id].begin();

            int right_idx = std::lower_bound(
                regions[id].begin(),
                regions[id].end(),
                make_pair(R + 1, 0)
            ) - regions[id].begin();

            int not_found = regions[id].size();

            // if the leftmost region contained within the removed part isn't
            // even completely in it, just give up on reducing the answer.
            if (left_idx != not_found && regions[id][left_idx].second <= R) {
                right_idx--;
                if (regions[id][right_idx].second > R) {
                    right_idx--;
                }

                // printf("subtracted %d from ans\n", (right_idx - left_idx + 1));
                ans -= (right_idx - left_idx + 1);
            }

            if (left_idx != 0) {
                int before = left_idx - 1;
                if (regions[id][before].second > R) {
                    // printf("added one to ans\n");
                    ans++;
                }
            }
        }

        printf("%d\n", ans);
    }
}