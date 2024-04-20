#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N; cin >> N;
    vector<int> even;
    vector<int> odd;

    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        if (x % 2 == 0) even.push_back(x);
        else odd.push_back(x);
    }

    // starts with even
    int group = 0;

    while (true) {
        // trying to make an even group
        if (group % 2 == 0) {
            if ((int) even.size() >= 1) {
                // int v = even.back();
                even.pop_back();
                // printf("Group %d: %d\n", group + 1, v);
            } else if ((int) odd.size() >= 2) {
                // int v1 = odd.back();
                odd.pop_back();
                // int v2 = odd.back();
                odd.pop_back();
                // printf("Group %d: %d, %d\n", group + 1, v1, v2);
            } else {
                // printf("Could not make group %d\n", group + 1);
                break;
            }
        } else {
            if ((int) odd.size() >= 1) {
                // int v = odd.back();
                odd.pop_back();
                // printf("Group %d: %d\n", group + 1, v);
            } else {
                // printf("Could not make group %d\n", group + 1);
                break;
            }
        }

        group++;
    }

    if (odd.size() % 2 == 1) {
        group--;
    }

    cout << group << endl;
}