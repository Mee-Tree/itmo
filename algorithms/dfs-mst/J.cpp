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

struct edge {
    int u, v, w;

    edge(int u, int v, int w)
        : u(u), v(v), w(w) { }

    friend bool operator < (edge a, edge b) {
        return a.w < b.w;
    }
};

vector<int> p, r;

int dsu_get(int u) {
    if (p[u] != u) {
        p[u] = dsu_get(p[u]);
    }
    return p[u];
}

void dsu_union(int u, int v) {
    u = dsu_get(u);
    v = dsu_get(v);

    if (u != v) {
        if (r[u] < r[v]) {
            swap(u, v);
        }
        p[v] = u;
        r[u] += r[u] == r[v];
    }
}

bool dsu_check(int u, int v) {
    return dsu_get(u) == dsu_get(v);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<edge> edges;
    for (int u, v, w; m-- && cin >> u >> v >> w;) {
        edges.emplace_back(u, v, w);
    }

    p.resize(n + 1);
    r.resize(n + 1);
    for (int i = 1; i <= n; ++i) { p[i] = i; }

    ll weight = 0;
    sort(edges.begin(), edges.end());
    for (edge e : edges) {
        if (!dsu_check(e.u, e.v)) {
            dsu_union(e.u, e.v);
            weight += e.w;
        }
    }

    cout << weight;
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


