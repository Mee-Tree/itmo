#include <iostream>

using namespace std;

const int N = 5e5;

int arr[N];
int buf[N];

long long merge(int l, int m, int r) {
    int i = l, j = m, id = 0;
    long long cnt = 0;
    while (i < m || j < r) {
        if (i == m) {
            buf[id] = arr[j++];
        } else if (j == r) {
            buf[id] = arr[i++];
        } else if (arr[i] <= arr[j]) {
            buf[id] = arr[i++];
        } else {
            buf[id] = arr[j++];
            cnt += (m - i);
        }
        id++;
    }
    for (i = l; i < r; i++)
        arr[i] = buf[i - l];
    return cnt;
}

long long mergeSort(int l, int r) {
    if (r - l < 2){
        return 0;
    }
    int mid = (l + r) / 2;
    return mergeSort(l, mid) + mergeSort(mid, r) + merge(l, mid, r);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    cout << mergeSort(0, n);

    return 0;
}