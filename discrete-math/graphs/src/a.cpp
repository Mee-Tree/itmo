#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
template<class T>
using graph = vector<vector<T>>;

void solve() {
    int n;
    cin >> n;

    graph<bool> g(n, vector<bool>(n));
    for (int i = 1; i < n; ++i) {
        string line;
        cin >> line;
        for (int j = 0; j < line.size(); ++j) {
            g[i][j] = g[j][i] = line[j] == '1';
        }
    }

    deque<int> q;
    for (int i = 0; i < n; ++i) {
        q.push_back(i);
    }

    for (int i = 0; i < n * (n - 1); ++i) {
        if (!g[q[0]][q[1]]) {
            int j = 2;
            while (!g[q[0]][q[j]]
                || !g[q[1]][q[j + 1]]) { ++j; }

            for (int t = 0; t < j / 2; ++t) {
                swap(q[j - t], q[1 + t]);
            }
        }
        q.push_back(q.front());
        q.pop_front();
    }

    for (int x : q) {
        cout << x + 1 << " ";
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
