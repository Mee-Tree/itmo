#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
using graph = vector<vector<int>>;

vector<int> prufer(graph& g) {
    vector<bool> killed(g.size());
    vector<int> degree(g.size());
    set<int> leaves;

    for (int i = 0; i < g.size(); ++i) {
        degree[i] = g[i].size();
        if (degree[i] == 1) {
            leaves.insert(i);
        }
    }

    vector<int> result;
    while (result.size() < g.size() - 2) {
        int leaf = *leaves.begin();
        leaves.erase(leaves.begin());
        killed[leaf] = true;

        int v = *find_if_not(all(g[leaf]), [&](int to) {
            return killed[to];
        });

        result.emplace_back(v);
        if (--degree[v] == 1) {
            leaves.insert(v);
        }
    }

    return result;
}

void solve() {
    int n;
    cin >> n;

    graph g(n);
    for (int u, v; cin >> u >> v;) {
        g[--u].emplace_back(--v);
        g[v].emplace_back(u);
    }

    for (int u : prufer(g)) {
        cout << u + 1 << " ";
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
