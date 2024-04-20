#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

#define int long long

#define TAKA 1
#define AOKI 2

string player_str(int player) {
    if (player == TAKA) return "Takahashi";
    else return "Aoki";
}

int other(int curr) {
    if (curr == TAKA) return AOKI;
    else return TAKA;
}

using board = array<int, 9>;

board state;
board values;

int get_winner() {
    for (int i = 0; i < 3; i++) {
        int fir = state[3 * i];
        if (fir != 0 && fir == state[3 * i + 1] && fir == state[3 * i + 2]) {
            return fir;
        }

        int fic = state[i];
        if (fic != 0 && fic == state[i + 3] && fic == state[i + 3 * 2]) {
            return fic;
        }
    }

    int tld = state[0];
    if (tld != 0 && tld == state[3 + 1] && tld == state[3 * 2 + 2]) {
        return tld;
    }

    int trd = state[2];
    if (trd != 0 && trd == state[3 + 1] && trd == state[3 * 2]) {
        return trd;
    }

    return 0;
}

// returns the winner
int dfs(int curr_player, int depth) {
    // if (depth == 6) return 0;

    // check direct placement: did other win?
    int winner = get_winner();
    if (winner != 0) return winner;


    // is there a move where i win? if so, take that,
    // otherwise this state is lost for this player

    int found_moves = 0;
    for (int i = 0; i < 9; i++) {
        // try placing here if empty
        if (state[i] == 0) {
            found_moves = 1;
            state[i] = curr_player;
            int get = dfs(other(curr_player), depth + 1);
            state[i] = 0;

            if (get == curr_player) {
                // i won!
                return curr_player;
            }
        }
    }

    // no moves, check by comparing scores
    if (!found_moves) {
        // printf("no moves:\n");
        // print_board();

        int taka_score = 0;
        int aoki_score = 0;
        for (int i = 0; i < 9; i++) {
            if (state[i] == TAKA) {
                taka_score += values[i];
            } else {
                aoki_score += values[i];
            }
        }

        if (taka_score > aoki_score) {
            // printf("winner is taka\n\n");
            return TAKA;
        } else {
            // printf("winner is aoki\n\n");
            return AOKI;
        }
    }

    // I lost
    return other(curr_player);
}

signed main(void) {
    // state = {0, 0, 0, 0, 0, 0, 1, 0, 0};
    // char win = get_winner();

    for (int i = 0; i < 9; i++) {
        cin >> values[i];
    }

    int win = dfs(TAKA, 0);
    if (win == TAKA) {
        printf("Takahashi\n");
    } else if (win == AOKI) {
        printf("Aoki\n");
    }
}