#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;

        int left = -1, right = n;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (arr[mid] < l) {
                left = mid;
            } else {
                right = mid;
            }
        }

        l = left + 1;
        left = -1, right = n;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            if (arr[mid] > r) {
                right = mid;
            } else {
                left = mid;
            }
        }

        r = right;
        cout << r - l << " ";
    }

    return 0;
}