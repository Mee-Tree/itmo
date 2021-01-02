#include <iostream>
#include <vector>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (int i = 0; i < k; ++i) {
        int num;
        cin >> num;
        int left = 0, right = n - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (num < arr[mid]) {
                right = mid;
            } else {
                left = mid;
            }
        }
        if (num - arr[left] <= arr[right] - num) {
            swap(left, right);
        }
        cout << arr[right] << "\n";
    }

    return 0;
}