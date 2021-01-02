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
using pii = pair<int, int>;
using pill = pair<int, ll>;

const ll INF = 6e18 + 1337;

struct edge {
    int u, v;
    ll w;

    edge(int u, int v, ll w)
        : u(u), v(v), w(w) {}
};

vector<bool> used;
vector<vector<int>> g;

void dfs(int u) {
    used[u] = true;
    for (int to : g[u]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

void solve() {
    int n, m, s;
    cin >> n >> m >> s;

    used.resize(n + 1);
    g.resize(n + 1);

    vector<edge> edges;
    vector<ll> d(n + 1, INF);
    for (int u, v; m-- && cin >> u >> v;) {
        ll w; cin >> w;
        g[u].emplace_back(v);
        edges.emplace_back(u, v, w);
    }

    d[s] = 0;
    vector<int> cycle;
    for (int i = 1; i <= n; ++i) {
        for (auto [u, v, w] : edges) {
            if (d[u] >= INF) { continue; }
            if (d[v] > d[u] + w) {
                d[v] = max(d[u] + w, -INF);

                if (i == n) {
                    cycle.emplace_back(v);
                }
            }
        }
    }

    for (int u : cycle) {
        if (!used[u]) {
            dfs(u);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (used[i]) {
            cout << "-";
        } else if (d[i] < INF) {
            cout << d[i];
        } else {
            cout << "*";
        }
        cout << endl;
    }
}

signed main() {
#ifdef LOCAL
    const string FILENAME = "local";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}


