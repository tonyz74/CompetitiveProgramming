#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void order(int& a, int &b) {
    if (a < b) std::swap(a, b);
}

char mem[1024][1024];

void put(char c, int w, int h, int x, int y) {
    for (int x_off = 0; x_off < w; x_off++) {
        for (int y_off = 0; y_off < h; y_off++) {
            mem[y + y_off][x + x_off] = c;
        }
    }
}

struct rect {
    int w, h;

    rect(int x, int y): w(x), h(y) {}
};

void print_rect(int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("%c", mem[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int x1, y1;
    int x2, y2;
    int x3, y3;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    order(x1, y1); 
    order(x2, y2); 
    order(x3, y3); 

    if (x1 == x2 && x2 == x3 && y1 + y2 + y3 == x1) {
        cout << x1 << endl;
        put('A', x1, y1, 0, 0); 
        put('B', x2, y2, 0, y1); 
        put('C', x3, y3, 0, y1 + y2);

        print_rect(x1);
        return 0;
    }

    // try the second config: L shaped
    {
        vector<rect> rects = {
            {x1, y1},
            {x2, y2},
            {x3, y3},
        };

        vector<char> chars = {'A', 'B', 'C'};

        vector<int> ordering = { 0, 1, 2 };
        do {
            vector<pair<int, int> > v = {
                {rects[ordering[0]].w, rects[ordering[0]].h},
                {rects[ordering[1]].w, rects[ordering[1]].h},
                {rects[ordering[2]].w, rects[ordering[2]].h}
            };

            for (int n_flip = 0; n_flip <= 3; n_flip++) {
                vector<int> flipped(3, 0);
                for (int i = 0; i < n_flip; i++) {
                    flipped[i] = 1;
                }
                std::reverse(flipped.begin(), flipped.end());

                do {
                    vector<rect> k;

                    for (int i = 0; i < 3; i++) {
                        int w, h; w = v[i].first; h = v[i].second;

                        if (flipped[i]) k.push_back(rect(h, w));
                        else k.push_back(rect(w, h));
                    }

                    if (k[0].w == k[1].w + k[2].w &&
                        k[1].h == k[2].h &&
                        k[0].h + k[1].h == k[0].w) {
                        put(chars[ordering[0]], k[0].w, k[0].h, 0, 0);
                        put(chars[ordering[1]], k[1].w, k[1].h, 0, k[0].h);
                        put(chars[ordering[2]], k[2].w, k[2].h, k[1].w, k[0].h);

                        printf("%d\n", k[0].w);
                        print_rect(k[0].w);
                        return 0;
                    }

                } while (next_permutation(flipped.begin(), flipped.end()));
            }

        } while (next_permutation(ordering.begin(), ordering.end()));
    }

    printf("%d\n", -1);
}