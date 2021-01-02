#include <bits/stdc++.h>

using namespace std;

set<int> accept[2];
vector<map<char, int>> go[2];

vector<bool> used;
vector<int> assoc;

bool dfs(int u, int v) {
    used[u] = true;
    if (accept[0].count(u) != accept[1].count(v)) {
        return false;
    }
    assoc[u] = v;
    bool res = true;
    for (auto [ch, u_to] : go[0][u]) {
        if (!go[1][v].count(ch)) {
            return false;
        }
        int v_to = go[1][v][ch];
        if (!used[u_to]) {
            res &= dfs(u_to, v_to);
        } else {
            res &= assoc[u_to] == v_to;
        }
    }
    return res;
}

void solve() {
    for (int t = 0; t < 2; ++t) {
        int n, m, k;
        cin >> n >> m >> k;
        used.resize(max((int) used.size(), n + 1));
        assoc.resize(used.size());

        for (int i = 0, state; i < k; ++i) {
            cin >> state;
            accept[t].insert(state);
        }

        go[t].resize(n + 1);
        for (int i = 0, u, v; i < m; ++i) {
            char sym;
            cin >> u >> v >> sym;
            go[t][u][sym] = v;
        }
    }

    cout << (dfs(1, 1) ? "YES" : "NO");
}

int main() {
    string file = "isomorphism";
#ifndef LOCAL
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
