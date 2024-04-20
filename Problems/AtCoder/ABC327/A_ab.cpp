#include <iostream>
#include <string>

using namespace std;

int main(void) {
    int N; cin >> N;
    string S; cin >> S;

    if (S.find("ab") != string::npos || S.find("ba") != string::npos) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}