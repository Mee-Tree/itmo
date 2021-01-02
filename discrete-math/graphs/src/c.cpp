#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
using graph = vector<vector<int>>;

void merge_sort(vector<int> &v, int left, int right) {
    if (left + 1 >= right) { return; }
    int mid = (left + right) / 2;
    merge_sort(v, left, mid);
    merge_sort(v, mid, right);

    vector<int> res(right - left);
    merge(v.begin() + left, v.begin() + mid,
          v.begin() + mid, v.begin() + right,
          res.begin(), [](int a, int b) {
                cout << 1 << " " << a << " " << b << endl;
                string response; cin >> response;
                return response == "YES";
            });
    copy(res.begin(), res.end(), v.begin() + left);
}

void solve() {
    int n;
    cin >> n;

    vector<int> v(n);
    iota(v.begin(), v.end(), 1);
    merge_sort(v, 0, n);

    cout << 0 << " ";
    for (int x : v) {
        cout << x << " ";
    }
}

int main() {
    const string FILE = "local";
#ifdef LOCAL
    freopen((FILE + ".in").c_str(), "r", stdin);
    freopen((FILE + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}