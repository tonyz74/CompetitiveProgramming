#include <iostream>

using namespace std;

int main(void) {
    int X, Y;
    cin >> X >> Y;

    if (Y > X && Y - X <= 2) printf("Yes\n");
    else if (X > Y && X - Y <= 3) printf("Yes\n");
    else printf("No\n");
}