#include <iostream>

using namespace std;

int main(void) {
    // n is stones, m is lily pads
    unsigned long long N, M;
    cin >> N >> M;

    // At the base case with no stones, there can be M + 1 frogs,
    // as they will fill up all the lily pads + the start.
    //
    // When you add a stone, the quantity will double: 2 * (M + 1),
    // because this new stone can act as the ending station, meaning
    // it can take all the frogs from when there were 0 stones.
    //
    // Now, it's a subproblem, as we know how many frogs there will be
    // when there are no stones.
    //
    // Therefore, adding a stone has the effect of doubling the previous
    // quantity. So, the result will be (M + 1) * pow(2, N).

    cout << ((M + 1) * (1ull << N)) << endl;
}
