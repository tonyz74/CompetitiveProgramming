#include <stdio.h>
#include <vector>

using namespace std;

int main(void) {
    int N;
    scanf("%d", &N);

    vector<vector<int> > blocks(N, vector<int>());

    int maxsum = 0;
    for (int i = 0; i < N; i++) {
        int n;
        int tmpsum = 0;
        blocks[i].reserve(100);

        while (true) {
            scanf("%d", &n);
            if (n == -1) {
                break;
            }

            tmpsum += n;
            blocks[i].push_back(n);
        }

        maxsum = max(maxsum, tmpsum);
    }

    
    // do an 0/1 knapsack on all of the towers, up to a weight
    // of the maximum possible height. find the intersection of
    // the heights that can be "perfectly made" for all the towers
    // (meaning that knapsack[W] == W where WT[i] = VAL[i]), and
    // find the maximum of that set of common heights.
    

    vector<int> ok_heights(maxsum + 1, 0);
    for (int i = 1; i <= maxsum; i++) {
        ok_heights[i] = i;
    }

    // loop through castles
    for (int castle_id = 0; castle_id < N; castle_id++) {
        vector<int> new_heights;
        new_heights.reserve(ok_heights.size());

        vector<int>& wt = blocks[castle_id];
        vector<int>& val = blocks[castle_id];


        vector<vector<int> > DP(
            // items to choose from -> blocks[castle_id]
            blocks[castle_id].size() + 1,
            // possible weights -> max value of ok_heights
            vector<int>(ok_heights[ok_heights.size() - 1] + 2, 0)
        );

        for (int i = 1; i < DP.size(); i++) {
            for (int j = 1; j < DP[0].size(); j++) {
                int other = 0;
                if (j - wt[i - 1] >= 0) {
                    other = DP[i - 1][j - wt[i - 1]] + val[i - 1];
                }

                DP[i][j] = max(other, DP[i - 1][j]);
            } 
        }

        int all_items = blocks[castle_id].size();
        for (int i = 0; i < ok_heights.size(); i++) {
            if (DP[all_items][ok_heights[i]] == ok_heights[i]) {
                new_heights.push_back(ok_heights[i]);
            }
        }

        ok_heights = new_heights;
    }

    int maxval = 0;
    for (int i = 0; i < ok_heights.size(); i++) {
        maxval = max(ok_heights[i], maxval);
    }

    printf("%d\n", maxval);
}
