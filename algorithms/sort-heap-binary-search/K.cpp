#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-6;

struct jewels {
    int v, w, id;
};

struct cmp {
    double p;
    cmp(double p) : p(p) {}
    bool operator()(jewels a, jewels b) {
        return (a.v - p * a.w > b.v - p * b.w);
    }
};

signed main() {
    int n, k;
    cin >> n >> k;

    vector<jewels> arr(n);
    double left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].v >> arr[i].w;
        right += arr[i].v;
        arr[i].id = i + 1;
    }

    while (fabs(left - right) > EPS) {
        double mid = (left + right) / 2.0;
        sort(arr.begin(), arr.end(), cmp(mid));
        double sum = 0;
        for(int i = 0; i < k; ++i) {
            sum += (arr[i].v - mid * arr[i].w);
        }
        if (sum >= 0){
            left = mid;
        } else {
            right = mid;
        }
    }

    sort(arr.begin(), arr.end(), cmp(left));
    for(int i = 0; i < k; ++i) {
        cout << arr[i].id << "\n";
    }

    return 0;
}