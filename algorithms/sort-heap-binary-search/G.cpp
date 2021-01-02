#include <iostream>
#include <vector>

using namespace std;

signed main() {
    int n, x, y;
    cin >> n >> x >> y;
    n--;
    int left = 0, right = min(x, y) * n;
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        int copies = mid / x + mid / y;
        if (copies < n) {
            left = mid;
        } else {
            right = mid;
        }
    }
    cout << right + min(x, y);
    return 0;
}