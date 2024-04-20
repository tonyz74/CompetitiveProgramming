#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <map>

using namespace std;

int n;
string garland;

int solve(int m, char fav) {
    bitset<2048> found;

    int j = 0;
    int favs_in_region = 0;
    if (garland[0] == fav) {
        found[0] = true;
        favs_in_region++;
    }

    int maxlen = 0;

    for (int i = 0; i < n; i++) {
        if (j < i) j = i;

        // printf("[i is now %d]\n", i);

        // just moved past a favorite
        if (i > 0 && found[i - 1]) {
            favs_in_region--;
            found[i - 1] = false;
        }

        if (!found[i] && garland[i] == fav) {
            favs_in_region++;
            found[i] = true;
        }

        if (!found[j] && garland[j] == fav) {
            favs_in_region++;
            found[j] = true;
        }

        while (j < n - 1 && (j - i + 1) <= favs_in_region + m) {
            // try advancing
            j++;

            if (!found[j] && garland[j] == fav) {
                favs_in_region++;
                found[j] = true;
            }
        }

        if (j - i + 1 > favs_in_region + m) {
            j--;
        }

        // for (int x = i; x <= j; x++) printf("%c", garland[x]);
        // printf("\n");

        // printf("favs in region: %d\n", favs_in_region);
        // printf("advanced j to %d\n", j);

        maxlen = max(maxlen, (j - i + 1));
        // printf("\n");
    } 

    return maxlen;
}

int main(void) {
    cin >> n;
    cin >> garland;

    map<pair<int, char>, int> answers;

    for (int m = 1; m <= n; m++) {
        for (char fav = 'a'; fav <= 'z'; fav++) {
            answers[make_pair(m, fav)] = solve(m, fav);
        }
    }

    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        int m; char c; cin >> m >> c;
        printf("%d\n", answers[make_pair(m, c)]);
    }

}