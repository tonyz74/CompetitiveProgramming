#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N; cin >> N;
    vector<int> a(N + 1);

    for (int i = 1; i <= N; i++) cin >> a[i];

    int average_photos = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            int total_sum = 0;
            int n_within = j - i + 1;

            for (int k = i; k <= j; k++) {
                total_sum += a[k];
            }

            int average = total_sum / n_within;
            if (total_sum % n_within != 0) continue;

            for (int k = i; k <= j; k++) {
                if (a[k] == average) {
                    average_photos++;
                    break;
                }
            }
        }
    }

    cout << average_photos << endl;
}