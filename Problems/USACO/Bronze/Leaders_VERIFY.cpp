#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;
string S;
vector<int> E;

bool is_id_lead(int loc, char c) {
    for (int i = 1; i <= N; i++) {
        if (S[i] == c && i < loc) return false;
        if (S[i] == c && i > E[loc]) return false;
    }

    return true;
}

int main(void) {
    cin >> N;
    cin >> S;
    S.insert(0, " ");

    E.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> E[i];
    }

    int total_cases = 0;

    for (int G_lead = 1; G_lead <= N; G_lead++) {
        if (S[G_lead] != 'G') continue;

        for (int H_lead = 1; H_lead <= N; H_lead++) {
            if (S[H_lead] != 'H') continue;

            // check if it works
            bool H_id_lead = is_id_lead(H_lead, 'H');
            bool G_id_lead = is_id_lead(G_lead, 'G'); 

            int ok = 0;

            if (H_id_lead && G_id_lead) {
                ok = 1;
            } else if (H_id_lead) {
                if (G_lead < H_lead && E[G_lead] >= H_lead) ok = 1;
            } else if (G_id_lead) {
                if (H_lead < G_lead && E[H_lead] >= G_lead) ok = 1;
            }

            if (ok == 1) {
                total_cases++;
                // printf("%d %d (%d %d)\n", G_lead, H_lead, (int) G_id_lead, (int) H_id_lead);
            }
        }
    }

    cout << total_cases << endl;
}