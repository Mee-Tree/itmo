#include <iostream>

using namespace std;

const int N = 5e5;

int arr[N];
int buf[N];

void merge(int l, int m, int r) {
    int i = l, j = m, id = 0;
    while (i < m || j < r) {
        if (i == m) {
            buf[id] = arr[j++];
        } else if (j == r) {
            buf[id] = arr[i++];
        } else if (arr[i] <= arr[j]) {
            buf[id] = arr[i++];
        } else {
            buf[id] = arr[j++];
        }
        id++;
    }
    for (i = l; i < r; i++)
        arr[i] = buf[i - l];
}

void mergeSort(int l, int r) {
    if (r - l < 2){
        return;
    }
    int mid = (l + r) / 2;
    mergeSort(l, mid);
    mergeSort(mid, r);
    merge(l, mid, r);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    mergeSort(0, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }

    return 0;
}