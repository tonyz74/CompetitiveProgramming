#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main(void) {
    int N; cin >> N;
    string S; cin >> S;
    S.insert(0, "*");           // just make it one indexed

    for (int K = 1; K <= N; K++) {
        set<string> existing;

        for (int start = 1; start <= N; start++) {
            string subst = S.substr(start, K);
            if ((int) subst.size() != K) break;

            // printf("subst: %s\n", subst.c_str());
            if (existing.count(subst)) goto next_K;
            existing.insert(subst);
        }

        printf("%d\n", K);
        return 0;

        next_K: (void) 0;
    }
}