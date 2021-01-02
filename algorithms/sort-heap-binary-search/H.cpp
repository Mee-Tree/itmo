#include <iostream>

using namespace std;

signed main() {
    long long n, w, h;
    cin >> w >> h >> n;
    long long left = 0, right = max(w, h) * n;
    while (left + 1 < right){
        long long mid = (left + right) / 2;
        if (1.0 * (mid / w) * (mid / h) < n){
            left = mid;
        } else{
            right = mid;
        }
    }
    cout << right;

    return 0;
}