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
using ll = long long;
using vvi = vector<vector<int>>;

const ll INF = 1e18 + 237;

namespace utils {

auto identity = [](auto x) { return x; };

auto every = [](auto &v) -> bool {
    return all_of(v.begin(), v.end(), identity);
};

} // end of utils

struct edge {
    int u, v;
    ll w;

    edge(int u, int v, ll w)
            : u(u), v(v), w(w) { }

    friend bool operator < (edge a, edge b) {
        return a.w < b.w;
    }
};

vector<bool> used;
vector<int> top;
int colour = 0;

void dfs1(int u, vvi &g) {
    used[u] = true;
    for (int to : g[u]) {
        if (!used[to]) {
            dfs1(to, g);
        }
    }
    top.push_back(u);
}

void dfs2(int u, vvi &gr, vector<int> &comp) {
    comp[u] = colour;
    for (int to : gr[u]) {
        if (comp[to] == -1) {
            dfs2(to, gr, comp);
        }
    }
}

void condensate(vvi &g, vvi &gr, int n, vector<int> &comp) {
    used.assign(n, false);
    top.clear();
    for (int i = 0; i < n; ++i) {
        if (!used[i]) { dfs1(i, g); }
    }

    colour = 0;
    for (int i = 0; i < n; ++i) {
        int v = top[top.size() - i - 1];
        if (comp[v] == -1) {
            dfs2(v, gr, comp);
            ++colour;
        }
    }
}

void dfs(int u, vvi &g) {
    used[u] = true;
    for (int to : g[u]) {
        if (!used[to]) {
            dfs(to, g);
        }
    }
}

bool check(int u, vvi &g, int n) {
    used.assign(n, false);
    dfs(u, g);
    return utils::every(used);
}

ll find_mst(int root, vector<edge> &es, int n) {
    vector<ll> min_edge(n, INF);
    ll res = 0;

    for (edge e : es) {
        min_edge[e.v] = min(min_edge[e.v], e.w);
    }

    for (int i = 0; i < n; ++i) {
        if (i == root) { continue; }
        res += min_edge[i];
    }


    vvi g(n), gr(n);
    for (edge e : es) {
        if (e.w == min_edge[e.v]) {
            g[e.u].push_back(e.v);
            gr[e.v].push_back(e.u);
        }
    }

    if (check(root, g, n)) { return res; }
    vector<int> comp(n, -1);
    condensate(g, gr, n, comp);

    vector<edge> new_edges;
    for (edge e : es) {
        if (comp[e.v] != comp[e.u]) {
            new_edges.emplace_back(comp[e.u], comp[e.v], e.w - min_edge[e.v]);
        }
    }
    res += find_mst(comp[root], new_edges, colour);
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vvi g(n);
    vector<edge> edges;
    for (int u, v, w; m-- && cin >> u >> v >> w; ) {
        edges.emplace_back(--u, --v, w);
        g[u].emplace_back(v);
    }

    if (check(0, g, n)) {
        cout << "YES" << endl;
        cout << find_mst(0, edges, n);
    } else {
        cout << "NO";
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


