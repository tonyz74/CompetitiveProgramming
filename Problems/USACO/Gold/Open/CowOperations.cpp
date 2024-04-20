#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(void) {
    string S; cin >> S;
    S = "." + S;
    int N = S.size();
    vector<map<char, int> > pfx(N + 1);

    map<char, int> now;
    now['C'] = 0;
    now['O'] = 0;
    now['W'] = 0;

    pfx[0] = now;
    for (int i = 1; i <= N; i++) {
        now[S[i]]++; 
        pfx[i] = now;
    }

    int Q; cin >> Q;
    for (int q = 1; q <= Q; q++) {
        int L, R; cin >> L >> R;

        int C = pfx[R]['C'] - pfx[L - 1]['C'];
        int O = pfx[R]['O'] - pfx[L - 1]['O'];
        int W = pfx[R]['W'] - pfx[L - 1]['W'];

        // printf("%d %d %d [%d, %d]\n", C, O, W, L, R);

        if ((W + C) % 2 == 1 && (W + O) % 2 == 0) {
            cout << "Y";
        } else {
            cout << "N";
        }
    }

    cout << endl;
}