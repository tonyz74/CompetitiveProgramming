#include <iostream>
#include <string>
#include <sstream>

using namespace std;
typedef long long i64;

int main(void) {
    i64 total = 0; 

    string S;
    while (cin >> S) {
        string id; cin >> id;
        id.resize(id.size() - 1);

        string line;
        std::getline(std::cin, line);
        std::istringstream istream(line);

        i64 red = 0, green = 0, blue = 0;
        i64 req_R = 0, req_G = 0, req_B = 0;

        // process entire line
        int x; string color;
        while (istream >> x) {
            istream >> color;

            bool should_reset = false;
            if (color[color.size() - 1] == ';') {
                should_reset = true;
            }

            if (!isalpha(color[color.size() - 1])) color.resize(color.size() - 1);

            if (color == "red") red += x;
            else if (color == "green") green += x;
            else if (color == "blue") blue += x;

            req_R = max(req_R, red);
            req_G = max(req_G, green);
            req_B = max(req_B, blue);

            if (should_reset) {
                red = 0;
                green = 0;
                blue = 0;
            }
        }

        total += (req_R * req_G * req_B);
    }

    cout << total << endl;
}