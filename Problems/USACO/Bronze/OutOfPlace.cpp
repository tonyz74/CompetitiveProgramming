#include <iostream>
#include <vector>

using namespace std;

int N;

int swap_to_left(vector<int> heights, int bessie_pos) {
    int swaps = 0;
    while (bessie_pos != 0 && heights[bessie_pos] < heights[bessie_pos - 1]) {
        int swap_pos = bessie_pos - 1;
        while (swap_pos > 0 && heights[swap_pos - 1] == heights[swap_pos]) {
            swap_pos--;
        }

        std::swap(heights[bessie_pos], heights[swap_pos]);
        bessie_pos = swap_pos;
        swaps++;
    } 

    return swaps;
}

int swap_to_right(vector<int> heights, int bessie_pos) {
    int swaps = 0;
    while (bessie_pos != N - 1 && heights[bessie_pos + 1] < heights[bessie_pos]) {
        int swap_pos = bessie_pos + 1;
        while (swap_pos < N - 1 && heights[swap_pos + 1] == heights[swap_pos]) {
            swap_pos++;
        }

        std::swap(heights[bessie_pos], heights[swap_pos]);
        bessie_pos = swap_pos;
        swaps++;
    }

    return swaps;
}

int main(void) {
    freopen("outofplace.in", "r", stdin);
    freopen("outofplace.out", "w", stdout);

    cin >> N;
    vector<int> heights(N);

    for (int i = 0; i < N; i++) cin >> heights[i];

    int bessie_pos = -1;
    int LR = -1;

    // remember to take care of a tall bessie later
    for (int i = 0; i < N - 1; i++) {
        if (heights[i + 1] < heights[i]) {
            bessie_pos = i + 1;
            break;
        }
    }
    
    if (bessie_pos == -1) {
        printf("%d\n", 0);
        return 0;
    }

    // now check if it was a too tall bessie, if so minus one
    // (if the array is consistent now, we were right, otherwise
    // it was a tall bessie and not a short one)
    int prev = heights[0];
    for (int i = 0; i < N; i++) {
        if (i == bessie_pos) continue;
        if (prev > heights[i]) {
            bessie_pos--;
            LR = 1;
            break;
        }
        prev = heights[i];
    }
    
    // bessie is too short
    if (LR == -1) {
        cout << swap_to_left(heights, bessie_pos) << endl; 
    }
    // bessie is too tall
    else {
        cout << swap_to_right(heights, bessie_pos) << endl;
    }
}