#include <iostream>
#include <vector>
#include <set>

using namespace std;

using p = pair<int, int>;

bool solve() {
    int N, M, K;
    set<int> folders;
    set<p> emails_above, emails_now, emails_below;
    vector<int> folder_refs(N + 1, 0);

    cin >> N >> M >> K;
    for (int i = 1; i <= K; i++) {
        folders.insert(i);
        int tgt; cin >> tgt;
        folder_refs[tgt]++;
        emails_now.insert(make_pair(i, tgt));
    }

    for (int i = K + 1; i <= M; i++) {
        int tgt; cin >> tgt;
        folder_refs[tgt]++;
        emails_below.insert(make_pair(i, tgt));
    }

    // scroll down folders only if:
    // 1. it's possible to. cannot scroll down if bottommost is N.
    // 2. the topmost folder isn't referenced by any emails.
    while (true) {
        int did_work = 0;

        if (folder_refs[*folders.begin()] == 0 && (*folders.rbegin()) != N) {
            folders.erase(folders.begin());
            folders.insert(*folders.rbegin() + 1);
        }



        if (!did_work) {
            break;
        }
    }

    return (emails_now.empty() && emails_below.empty() && emails_above.empty());
}

int main(void) {
    int T; cin >> T;
    while (T--) {
        solve();
    }
}