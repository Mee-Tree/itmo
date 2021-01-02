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

vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<int> tin, up;
int t = 0;

vector<int> bridges;

void dfs(int u, int p = -1) {
    used[u] = true;
    tin[u] = up[u] = t++;
    for (auto [to, ind] : g[u]) {
        if (to == p) { continue; }
        if (used[to]) {
            up[u] = min(up[u], tin[to]);
        } else {
            dfs(to, u);
            up[u] = min(up[u], up[to]);
            if (up[to] > tin[u]) {
                bridges.emplace_back(ind);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    g.resize(n + 1);
    used.resize(n + 1);
    up.resize(n + 1);
    tin.resize(n + 1);
    for (int i = 1, u, v; i <= m && cin >> u >> v; ++i) {
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int u = 1; u <= n; ++u) {
        if (!used[u]) { dfs(u); }
    }

    cout << bridges.size() << endl;
    sort(bridges.begin(), bridges.end());
    for (int bridge : bridges) {
        cout << bridge << " ";
    }
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


