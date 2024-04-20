#include <iostream>
#include <vector>
#include <string>

using namespace std;

int chars[1024];       // state array
bool pwin[1024][1024]; // possible winners

void clear() {
    for (int i = 0; i < 1024; i++) chars[i] = 0;
}

void set_winners(vector<char> vc) {
    if (vc[0] == vc[1] && vc[1] == vc[2]) {
        // printf("%c, %c, %c\n", vc[0], vc[1], vc[2]);
        int norm = vc[0] - 'A';
        pwin[norm][norm] = true;
        // printf("setting %d\n", norm);
        return;
    }

    int combi[3][3] = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 2, 0}
    };

    for (int c = 0; c < 3; c++) {
        int i1 = combi[c][0]; int i2 = combi[c][1]; int i3 = combi[c][2];

        if (vc[i1] == vc[i2]) {
            int norm1 = vc[i1] - 'A';
            int norm2 = vc[i3] - 'A';

            pwin[norm1][norm2] = true;
            pwin[norm2][norm1] = true;
        }
    }
}

int main(void) {
    freopen("tttt.in", "r", stdin);
    freopen("tttt.out", "w", stdout);

    clear();

    string gameboard[3];
    for (int i = 0; i < 3; i++) cin >> gameboard[i];

    for (int off = 0; off < 3; off++) {
        set_winners({ gameboard[0][off], gameboard[1][off], gameboard[2][off] });
        set_winners({ gameboard[off][0], gameboard[off][1], gameboard[off][2] });
    }

    set_winners({ gameboard[0][0], gameboard[1][1], gameboard[2][2] });
    set_winners({ gameboard[0][2], gameboard[1][1], gameboard[2][0] });
    
    int individuals = 0;
    for (int i = 0; i <= 50; i++) {
        if (pwin[i][i]) {
            // printf("individual: %d\n", i);
            individuals += 1;
        }
    }

    int teams = 0;
    for (int a = 0; a <= 50; a++) {
        for (int b = 0; b <= 50; b++) {
            if (a == b) continue;
            teams += pwin[a][b];
        }
    }
    teams /= 2;

    cout << individuals << endl << teams << endl;
}