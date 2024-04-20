#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
    string S; int N;
    cin >> S >> N;

    // int len = S.size();

    for (int i = 1; i <= 10; i++) {
        // printf("i = %3d: ", i);
        string new_str = S;
        new_str += S.back();
        // printf("%c\n", S.back());
        for (int i = 0; i < (int) S.size() - 1; i++) {
            new_str += S[i];
        }

        S = new_str;
        // for (int chr = 0; chr < (int) S.size(); chr++) {
        //     if (chr % len == 0) {
        //         printf(".");
        //     }
        //     printf("%c", S[chr]);
        // }
        // printf("\n");

        if ((int) S.size() > N) {
            printf("%c\n", S[N - 1]);
            break;
        }
    }
}