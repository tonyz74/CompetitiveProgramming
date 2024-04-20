#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define RIGHT 1
#define LEFT (-1)

int main(void) {
    int N; cin >> N;
    vector<int> A(N);

    int total_len = 0;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        total_len += A[i];
    }

    int oi = 0;
    string output_buf(total_len, '.');

    int pos = 0;
    int direction = RIGHT;

    while (oi != total_len) {
        // cout << oi << " " << direction << endl;
        // cout << output_buf << ", at " << pos << endl;
        // for (int i = 0; i < N; i++) {
        //     cout << A[i] << " ";
        // }
        // cout << endl;

        if (pos == 0) {
            direction = RIGHT;
            output_buf[oi++] = 'R';
            pos++;
            A[0]--;
        } else if (pos == N) {
            direction = LEFT;
            output_buf[oi++] = 'L';
            pos--;
            A[N - 1]--;
        } else {
            
            // just keep going right, we don't care
            if (direction == RIGHT) {

                while (pos != N && A[pos] != 0) {
                    output_buf[oi++] = 'R';
                    A[pos]--;
                    pos++;
                }

                direction = LEFT;

            } else {
                // when we go left, we just need to make sure we're able to come back
                while (pos != 0 && (A[pos - 1] >= 3 || A[pos] == 0)) {
                    output_buf[oi++] = 'L';
                    pos--;
                    A[pos]--;
                }

                direction = RIGHT;

            }

        }
    }

    cout << output_buf << endl;
}