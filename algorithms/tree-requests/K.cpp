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


int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void dfs(int u, int p = 1) {
    up[u].push_back(p);
    for (int to : g[u]) {
        if (to != p) {
            depth[to] = depth[u] + 1;
            dfs(to, u);
        }
    }
}

void precalc() {
    dfs(1);
    for (int i = 1; (1 << (i - 1)) < g.size(); ++i) {
        for (int u = 1; u < g.size(); ++u) {
            up[u].push_back(up[up[u][i - 1]][i - 1]);
        }
    }
}

vector<vector<int>> pref;
int pref_min(int u, int d) {
    int nd = min(d, (int)pref[u].size() - 1);
    return pref[u][nd];
}

int query(int u, int d) {
    int res = pref_min(u, d);
    for (int v = u; v; v = parent[v]) {
        int nd = d - dist(u, v);
        if (nd < 0) continue;
        res = min(res, pref_min(v, nd));
    }
    return res;
}

void resize_all(int sz) {
    g.resize(sz);
    up.resize(sz);
    pref.resize(sz);
    depth.resize(sz);
    size_.resize(sz);
    parent.resize(sz);
}

void solve() {
    int n, m;
    scanf("%d %d", &n, &m);

    resize_all(n + 1);
    for (int _ = 1, u, v; _ < n; ++_) {
        scanf("%d %d", &u, &v);
        g[u].insert(v);
        g[v].insert(u);
    }

    precalc();
    decompose(1);


    for (int u = 1; u <= n; ++u) {
        for (int v = u; v; v = parent[v]) {
            int d = dist(u, v);
            if (d >= pref[v].size()) {
                pref[v].resize(d + 1, INF);
            }
            pref[v][d] = min(pref[v][d], u);
        }
    }

    for (int u = 1; u <= n; ++u) {
        for (int d = 1; d < pref[u].size(); ++d) {
            pref[u][d] = min(pref[u][d], pref[u][d - 1]);
        }
    }

    while (m--) {
        int u, d;
        scanf("%d %d", &u, &d);
        printf("%d\n", query(u, d));
    }
}

int main() {
#ifdef LOCAL
    const string FILENAME = "req";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    solve();
    return 0;
}
