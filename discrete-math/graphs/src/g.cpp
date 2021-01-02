#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
using graph = vector<vector<int>>;

vector<bool> used;
vector<int> color;

void dfs(int u, graph& g) {
    used[u] = true;
    for (int to : g[u]) {
        if (!used[to]) {
            dfs(to, g);
        }
    }

    set<int> clrs;
    for (int to : g[u]) {
        clrs.insert(color[to]);
    }

    for (int clr = 1; ; ++clr) {
        if (clrs.count(clr) == 0) {
            color[u] = clr;
            break;
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    graph g(n);
    for (int u, v; m-- && cin >> u >> v;) {
        g[--u].emplace_back(--v);
        g[v].emplace_back(u);
    }

    int u = 0;
    while (g[u].size() % 2) { ++u; }
    assert(u < n);
    color.resize(n);
    used.resize(n);
    dfs(u, g);

    int mx = 0;
    for (auto& gu : g) {
        mx = max(mx, (int) gu.size());
    }

    cout << (mx % 2 > 0 ? mx : mx + 1) << endl;
    for (int clr : color) {
        cout << clr << endl;
    }
}

signed main() {
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