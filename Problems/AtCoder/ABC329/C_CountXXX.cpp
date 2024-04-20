#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(void) {
    int N; cin >> N;
    string S; cin >> S;

    map<char, int> max_chars;

    int i = 0;
    while (i < N) {
        int chr = S[i];
        int len = 1;
        while (i != N - 1  && S[i + 1] == S[i]) {
            i++;
            len++;
        }

        max_chars[chr] = max(max_chars[chr], len);
        i++;
    }

    int sum = 0;
    for (pair<char, int> val: max_chars) {
        sum += val.second;
    }
    printf("%d\n", sum);
}