#include <iostream>
#include <vector>

using namespace std;

int pos = 1;
vector<int> out;
vector<vector<int> > infos;

bool valid() {
    for (int starting = 1; starting <= pos; starting++) {
        int min_val = out[starting];
        int max_val = out[starting];

        for (int ending = starting; ending <= pos; ending++) {
            min_val = min(out[ending], min_val);
            max_val = max(out[ending], max_val);

            int req = infos[starting][ending];

            if (req != (max_val - min_val)) {
                // printf("%d -> %d, req = %d, val = %d (%d, %d)\n", starting, ending, req, (max_val - min_val), max_val, min_val);
                return false;
            }
        }
    }

    return true;
}

int main(void) {
    int N; cin >> N;
    infos.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        infos[i].resize(N + 1);

        for (int j = i; j <= N; j++) {
            int x; cin >> x;
            infos[i][j] = x;
        }
    }

    out.resize(N + 1);
    out[pos++] = 0;

    for (; pos <= N; pos++) {
        int diff = infos[pos - 1][pos];
        int val_lt = out[pos - 1] - diff;
        int val_gt = out[pos - 1] + diff;

        // try the less than
        out[pos] = val_gt;
        if (valid()) {
            continue;
        }

        out[pos] = val_lt;
        if (!valid()) {
            printf("%d: ERROR\n", pos);
            exit(-1);
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << out[i];

        if (i != N) cout << " ";
    }
    cout << endl;
}