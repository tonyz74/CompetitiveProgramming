#include <iostream>
#include <vector>
#include <string>

using namespace std;

int iv[1024] = {0};

int main(void) {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    int N; cin >> N;
    int M; cin >> M;

    vector<string> spotty(N);
    vector<string> plain(N);
    
    for (int i = 0; i < N; i++) cin >> spotty[i];
    for (int i = 0; i < N; i++) cin >> plain[i];

    iv[(int) 'A'] = 0;
    iv[(int) 'C'] = 1;
    iv[(int) 'T'] = 2;
    iv[(int) 'G'] = 3;

    long long valids = 0;

    for (int x = 0; x < M; x++)
    for (int y = x + 1; y < M; y++)
    for (int z = y + 1; z < M; z++) {

        bool in_spotty[1024] = {false};
        for (int n = 0; n < N; n++) {
            const string& gene = spotty[n];
            int val = iv[(int) gene[x]] * 100 + iv[(int) gene[y]] * 10 + iv[(int) gene[z]];
            in_spotty[val] = true;
        }

        for (int n = 0; n < N; n++) {
            const string& gene = plain[n];
            int val = iv[(int) gene[x]] * 100 + iv[(int) gene[y]] * 10 + iv[(int) gene[z]];
            if (in_spotty[val]) goto invalid_triple;
        }

        valids++;
        invalid_triple: (void) 1;
    }

    cout << valids << endl;
}