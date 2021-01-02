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

#define all(v) v.begin(), v.end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pill = pair<int, ll>;

const ll INF = 1e18 + 1337;

vector<vector<pii>> g;
vector<vector<pill>> new_g;
vector<vector<ll>> vertex;
vector<bool> used;

int n, m;
ll t, M;

void build(int u, ll ost) {
    if (used[vertex[u][ost]]) { return; }
    used[vertex[u][ost]] = true;

    for (auto [to, w] : g[u]) {
        ll new_ost = (ost + w) % M;
        new_g[vertex[u][ost]].emplace_back(
                vertex[to][new_ost], w);

        if (to == n && new_ost == t % M) {
            used[vertex[n][t % M]] = true;
            return;
        }
        build(to, new_ost);
    }
}

void solve() {
    cin >> n >> m;
    g.resize(n + 1);
    for (int u, v, w; m-- && cin >> u >> v >> w;) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    cin >> t;
    if (g[n].empty()) {
        cout << "Impossible";
        return;
    }

    M = 2 * g[n][0].second;
    vertex.resize(n + 1, vector<ll>(M, -1));

    int ind = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < M; ++j) {
            vertex[i][j] = ++ind;
        }
    }

    used.resize(n * M + 1);
    new_g.resize(n * M + 1);
    build(1, 0);

    ll s = vertex[1][0];
    ll f = vertex[n][t % M];

    if (used[f]) {
        vector<ll> d(n * M + 1, INF);
        set<pill> q{{d[s] = 0, s}};

        while (!q.empty()) {
            auto [_, u] = *q.begin();
            q.erase(q.begin());

            for (auto [to, w] : new_g[u]) {
                if (d[to] > d[u] + w) {
                    q.erase({d[to], to});
                    d[to] = d[u] + w;
                    q.emplace(d[to], to);
                }
            }
        }

        if (d[f] <= t) {
            cout << "Possible";
            return;
        }
    }

    cout << "Impossible";
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