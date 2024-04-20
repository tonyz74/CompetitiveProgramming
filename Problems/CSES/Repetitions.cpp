#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string DNA; cin >> DNA;

    int max_len = 0;
    int candidate = 1;

    for (int i = 0; i < DNA.length(); i++) {
        candidate = 1;

        while (i + 1 < DNA.length() && DNA[i + 1] == DNA[i]) {
            i++;
            candidate++;
        }

        max_len = max(max_len, candidate);
    }

    cout << max_len << endl;
}