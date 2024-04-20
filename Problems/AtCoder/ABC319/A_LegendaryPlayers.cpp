#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    vector<pair<string, int>> data;
    data.push_back(make_pair("tourist", 3858));
    data.push_back(make_pair("ksun48", 3679)); 
    data.push_back(make_pair("Benq", 3658)); 
    data.push_back(make_pair("Um_nik", 3648)); 
    data.push_back(make_pair("apiad", 3638)); 
    data.push_back(make_pair("Stonefeang", 3630)); 
    data.push_back(make_pair("ecnerwala", 3613)); 
    data.push_back(make_pair("mnbvmar", 3555)); 
    data.push_back(make_pair("newbiedmy", 3516)); 
    data.push_back(make_pair("semiexp", 3481));

    string uname;
    cin >> uname;

    for (int i = 0; i < data.size(); i++) {
        if (data[i].first == uname) {
            cout << data[i].second << endl;
            return 0;
        }
    }
}