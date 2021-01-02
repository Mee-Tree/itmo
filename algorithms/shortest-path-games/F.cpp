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
map<int, vector<ll>> d;

void dijkstra(int s) {
    vector<ll>& dd = d[s];
    set<pill> q{{dd[s] = 0, s}};

    while (!q.empty()) {
        auto [_, u] = *q.begin();
        q.erase(q.begin());

        for (auto [to, w] : g[u]) {
            if (dd[to] > dd[u] + w) {
                q.erase({dd[to], to});
                dd[to] = dd[u] + w;
                q.emplace(dd[to], to);
            }
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    g.resize(n + 1);
    for (int u, v, w; m-- && cin >> u >> v >> w;) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    int a, b, c;
    cin >> a >> b >> c;

    vector<int> houses = {a, b, c};
    for (int s : houses) {
        d[s].assign(n + 1, INF);
        dijkstra(s);
    }

    sort(all(houses));
    ll result = INF;
    do {
        a = houses[0], b = houses[1], c = houses[2];
        result = min(result, d[a][b] + d[b][c]);
    } while (next_permutation(all(houses)));

    cout << (result < INF ? result : -1);
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


