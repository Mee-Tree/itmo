#include <bits/stdc++.h>
#pragma GCC optimize("-Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("arch=corei7-avx")

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
using ll = long long;

const int INF = 1e9;

vector<set<int>> g;

vector<int> size_;
void update_size(int u, int p = 0) {
    size_[u] = 1;
    for (int to : g[u]) {
        if (to == p) continue;
        update_size(to, u);
        size_[u] += size_[to];
    }
}

int cur_size;
int find_centroid(int u, int p = 0) {
    for (int to : g[u]) {
        if (to != p && size_[to] > cur_size / 2) {
            return find_centroid(to, u);
        }
    }
    return u;
}

vector<int> parent;
void decompose(int u, int p = 0) {
    update_size(u);
    cur_size = size_[u];
    int centroid = find_centroid(u);
    parent[centroid] = p;
    for (int to : g[centroid]) {
        g[to].erase(centroid);
        decompose(to, centroid);
    }
    g[centroid].clear();
}

vector<int> depth;
vector<vector<int>> up;
int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }

    int delta = depth[v] - depth[u];
    for (int i = up[u].size() - 1; i >= 0; --i) {
        if ((1 << i) & delta) {
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
}

void precalc() {
    function<void(int, int)> dfs = [&](int u, int p) {
        up[u].push_back(p);
        for (int to : g[u]) {
            if (to != p) {
                depth[to] = depth[u] + 1;
                dfs(to, u);
            }
        }
    };
    dfs(1, 1);
    for (int i = 1; (1 << (i - 1)) < g.size(); ++i) {
        for (int u = 1; u < g.size(); ++u) {
            up[u].push_back(up[up[u][i - 1]][i - 1]);
        }
    }
}

ll dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

vector<int> color;
vector<array<ll, 2>> cur;
vector<array<ll, 2>> next_;
vector<array<int, 2>> clr_size;

void change_color(int u) {
    color[u] ^= 1;
    int d = color[u] ? 1 : -1;
    for (int v = u; ; v = parent[v]) {
        clr_size[v][0] -= d;
        clr_size[v][1] += d;
        cur[v][0] -= dist(u, v) * d;
        cur[v][1] += dist(u, v) * d;
        if (!parent[v]) break;
        next_[v][0] -= dist(u, parent[v]) * d;
        next_[v][1] += dist(u, parent[v]) * d;
    }
}

ll query(int u) {
    int clr = color[u];
    ll res = cur[u][clr];
    for (int prev = u, v = parent[u]; v; prev = v, v = parent[v]) {
        res += cur[v][clr] - next_[prev][clr];
        res += (clr_size[v][clr] - clr_size[prev][clr]) * dist(u, v);
    }
    return res;
}

void resize_all(int sz) {
    g.resize(sz);
    up.resize(sz);
    cur.resize(sz);
    depth.resize(sz);
    color.resize(sz);
    next_.resize(sz);
    size_.resize(sz);
    parent.resize(sz);
    clr_size.resize(sz);
}

void solve() {
    int n, m;
    cin >> n >> m;

    resize_all(n + 1);
    for (int _ = 1, u, v; _ < n; ++_) {
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }

    precalc();
    decompose(1);

    for (int u = 1; u <= n; ++u) {
        for (int v = u; ; v = parent[v]) {
            clr_size[v][0]++;
            cur[v][0] += dist(u, v);
            if (!parent[v]) break;
            next_[v][0] += dist(u, parent[v]);
        }
    }

    while (m--) {
        int cmd, u;
        cin >> cmd >> u;
        if (cmd == 1) {
            change_color(u);
        } else {
            cout << query(u) << endl;
        }
    }
}

signed main() {
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
