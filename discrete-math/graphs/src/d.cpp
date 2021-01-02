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
            g[i][j] = (line[j] == '1');
            g[j][i] = (line[j] == '0');
        }
    }

    int u = 0;
    vector<int> path(1, u++);
    while (path.size() < n) {
        auto it = path.begin();
        while (it != path.end() && g[*it][u]) { ++it; }
        path.insert(it, u++);
    }

    u = path[0];
    vector<int> cycle;
    int i = (int) path.size() - 1;
    for (; i >= 2; --i) {
        if (g[path[i]][u]) { break; }
    }
    cycle.insert(cycle.begin(), path.begin(),
                 path.begin() + ++i);

    for (auto last = path.begin() + i; i < n; ++i) {
        u = path[i];
        for (auto it = cycle.begin(); it != cycle.end(); ++it) {
            if (g[u][*it]) {
                cycle.insert(it, last, path.begin() + i + 1);
                last = path.begin() + i + 1;
                break;
            }
        }
    }

    for (int x : cycle) {
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
