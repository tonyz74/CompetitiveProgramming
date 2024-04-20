#include <iostream>
#include <string>

using namespace std;

int main(void) {
    string S; cin >> S;

    string res = "";
    for (int i = 0; i < (int) S.length(); i++) {
        res.push_back(S[i]);

        int b = res.length() - 1;
        if (res[b] == 'C' && res[b - 1] == 'B' && res[b - 2] == 'A') {
            res.resize(res.length() - 3);
            // printf("after: %s\n", res.c_str());
        }
    }

    printf("%s\n", res.c_str());
}