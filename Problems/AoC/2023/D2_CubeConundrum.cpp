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
        i64 id_int = atoi(id.c_str());

        string line;
        std::getline(std::cin, line);
        std::istringstream istream(line);

        int red = 0;
        int green = 0;
        int blue = 0;

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

            if (red > 12 || green > 13 || blue > 14) goto impossible;

            if (should_reset) {
                red = 0;
                green = 0;
                blue = 0;
            }
        }

        total += id_int;
        impossible: (void) 0;
    }

    cout << total << endl;
}