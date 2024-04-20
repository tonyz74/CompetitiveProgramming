#include <iostream>
#include <vector>

using namespace std;

bool is_prime(int i) {
    for (int f = 2; f * f <= i; f++) {
        if (i % f == 0) {
            return false;
        }
    }

    return true;
}

vector<int> input_numbers;
int n_primes = 0;
int N;
int K;

void dfs(int index, int n_picked, int current_sum) {
    if (index == N) {
        if (n_picked == K && is_prime(current_sum)) {
            n_primes++;
        }
        return;
    }

    dfs(index + 1, n_picked + 1, current_sum + input_numbers[index]);
    dfs(index + 1, n_picked, current_sum);
}

int main(void) {
    cin >> N >> K;

    input_numbers.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> input_numbers[i];
    }

    dfs(0, 0, 0);
    cout << n_primes << endl;
}