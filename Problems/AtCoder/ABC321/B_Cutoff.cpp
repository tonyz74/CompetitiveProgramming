#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    int N, X;
    cin >> N >> X;

    vector<int> scores(N - 1, 0);
    for (int i = 0; i < N - 1; i++) {
        cin >> scores[i];
    }

    sort(scores.begin(), scores.end());

    int overall_score = 0;
    for (int i = 1; i < scores.size() - 1; i++) {
        overall_score += scores[i];
    }

    int diff = X - overall_score;

    int result = -1;

    if (diff <= 0) {
        result = 0;
    }
    
    else if (diff <= scores[0]) {
        result = 0;
    }

    // this will become the new max score, and be removed
    else if (diff >= scores.back()) {
        // printf("overall score: %d, scores.back(): %d\n", overall_score, scores.back());
        result = (overall_score + scores.back()) >= X ? scores.back() : -1;
    }

    else {
        result = diff;
    }

    printf("%d\n", result);
}