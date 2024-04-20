#include <iostream>
#include <queue>

using namespace std;

int main(void) {
    int N;
    cin >> N;

    priority_queue<int> fruits; 

    for (int i = 0; i < N; i++) {
        int weight;
        cin >> weight;
        fruits.push(weight * -1);
    }

    int tot = 0;

    while (!fruits.empty()) {
        int top1 = fruits.top() * -1;
        fruits.pop();
        int top2 = fruits.top() * -1;
        fruits.pop();

        int combined = top1 + top2;
        tot += combined;
        
        if (fruits.empty()) {
            break;
        }
        fruits.push(combined * -1);
    }

    cout << tot << endl;
}
