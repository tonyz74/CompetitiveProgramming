#include <map>
#include <iostream>

using namespace std;

int main(void) {
	map<int, int> m;
	m[2] = 6;
	m[3] = 8;
	
	auto new_it = m.begin();
	for (auto i = m.begin(); i != m.end(); i = new_it) {
        cout << i->first << ", " << i->second << endl;

		if (i->second / 2 != 0) {
			// OK. Will be iterated later on.
			m[i->first * 2] = i->second / 2;
		}

		new_it = i; new_it++;
		// OK. Won't cause segfaults.
		m.erase(i->first);
	}
}