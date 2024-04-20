#include <iostream>

using namespace std;

int main(void) {

    printf("\t|");
    for (int col = 0; col <= 9; col++) {
        printf("y %6d   | ", col);
    }
    printf("\n");

    for (int x = 0; x <= 9; x++) {
        printf("x %d:\t|", x);
        for (int y = 0; y <= 9; y++) {
            printf("  %6d   | ", (1 << x) - (1 << y));
        }
        printf("\n");
    }

}