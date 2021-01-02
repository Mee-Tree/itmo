#include <iostream>
#include <vector>

using namespace std;

signed main() {
    const int SIZE = 101;
    vector<int> cnt(SIZE);
    int cur;
    while (cin >> cur) {
        cnt[cur]++;
    }
    for (int i = 0; i < SIZE; ++i) {
        while (cnt[i]--) {
            cout << i << " ";
        }
    }

    return 0;
}