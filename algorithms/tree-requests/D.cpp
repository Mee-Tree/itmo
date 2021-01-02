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
    int m;
    cin >> m;

    int size = m + 10;
    vector<vector<int>> up(size, vector<int>(log2(size) + 1));
    vector<int> depth(size), p(size);
    vector<bool> eaten(size, true);
    up[1].assign(log2(size) + 1, 1);
    eaten[1] = false; p[1] = 1;

    int cur = 1;
    auto add = [&](int parent) {
        depth[++cur] = depth[parent] + 1;
        p[cur] = up[cur][0] = parent;
        eaten[cur] = false;
        for (int i = 1; i < up[cur].size(); ++i) {
            up[cur][i] = up[up[cur][i - 1]][i - 1];
        }
    };

    function<int(int)> find_alive = [&](int u) {
        if (!eaten[u]) return u;
        return p[u] = find_alive(p[u]);
    };

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
        return find_alive(p[u]);
    };

    for (int _ = 0, u, v; _ < m; ++_) {
        char cmd;
        cin >> cmd >> u;
        if (cmd == '?') {
            cin >> v;
            cout << lca(u, v) << endl;
        } else if (cmd == '-') {
            eaten[u] = true;
        } else add(u);
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
