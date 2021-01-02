#include <bits/stdc++.h>

/*
░░░░░░▄▀▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒█
░░░░░█▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒█
░░░░█▒▒▄▀▀▀▀▀▄▄▒▒▒▒▒▒▒▒▒▄▄▀▀▀▀▀▀▄
░░▄▀▒▒▒▄█████▄▒█▒▒▒▒▒▒▒█▒▄█████▄▒█
░█▒▒▒▒▐██▄████▌▒█▒▒▒▒▒█▒▐██▄████▌▒█
▀▒▒▒▒▒▒▀█████▀▒▒█▒░▄▒▄█▒▒▀█████▀▒▒▒█
▒▒▐▒▒▒░░░░▒▒▒▒▒█▒░▒▒▀▒▒█▒▒▒▒▒▒▒▒▒▒▒▒█
▒▌▒▒▒░░░▒▒▒▒▒▄▀▒░▒▄█▄█▄▒▀▄▒▒▒▒▒▒▒▒▒▒▒▌
▒▌▒▒▒▒░▒▒▒▒▒▒▀▄▒▒█▌▌▌▌▌█▄▀▒▒▒▒▒▒▒▒▒▒▒▐
▒▐▒▒▒▒▒▒▒▒▒▒▒▒▒▌▒▒▀███▀▒▌▒▒▒▒▒▒▒▒▒▒▒▒▌
▀▀▄▒▒▒▒▒▒▒▒▒▒▒▌▒▒▒▒▒▒▒▒▒▐▒▒▒▒▒▒▒▒▒▒▒█
▀▄▒▀▄▒▒▒▒▒▒▒▒▐▒▒▒▒▒▒▒▒▒▄▄▄▄▒▒▒▒▒▒▄▄▀
▒▒▀▄▒▀▄▀▀▀▄▀▀▀▀▄▄▄▄▄▄▄▀░░░░▀▀▀▀▀▀
▒▒▒▒▀▄▐▒▒▒▒▒▒▒▒▒▒▒▒▒▐
*/

using namespace std;

const int INF = 2e9;

void solve() {
    int n, m;
    cin >> n;

    int size = n + 1;
    vector<vector<int>> up(size, vector<int>(log2(size) + 1));
    vector<vector<int>> children(size);
    up[1].assign(log2(size) + 1, 1);

    for (int _ = 1, u, v; _ < n; ++_) {
        cin >> u >> v;
        children[u].push_back(v);
        children[v].push_back(u);
    }

    vector<int> depth(size);
    vector<bool> used(size);
    function<void(int, int, int)> dfs = [&](int u, int p, int d) {
        used[u] = true;
        depth[u] = d;
        up[u][0] = p;
        for (int i = 1; i < up[u].size(); ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for (int to : children[u]) {
            if (!used[to]) dfs(to, u, d + 1);
        }
    };
    dfs(1, 1, 0);

    auto lca = [&](int u, int v) {
        if (depth[u] > depth[v]) swap(u, v);

        int delta = depth[v] - depth[u];
        for (int i = up[u].size() - 1; i >= 0 && delta; --i) {
            if ((1 << i) <= delta) {
                delta -= (1 << i);
                v = up[v][i];
            }
        }
        if (u == v) return u;

        for (int i = up[u].size() - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    };

    used.assign(size, false);
    vector<int> jump(size, -INF);
    function<int(int)> cnt = [&](int u) {
        int res = 0;
        used[u] = true;
        for (int to : children[u]) {
            if (used[to]) continue;
            res += cnt(to);
            jump[u] = max(jump[u], jump[to] - 1);
        }
        return res + (jump[u] > 0);
    };

    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        int lca_ = lca(u, v);
        jump[u] = max(jump[u], depth[u] - depth[lca_]);
        jump[v] = max(jump[v], depth[v] - depth[lca_]);
    }

    cout << n - 1 - cnt(1);
}

int main() {
#ifdef LOCAL
    const string FILENAME = "req";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
