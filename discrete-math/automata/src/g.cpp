#include <bits/stdc++.h>

using namespace std;

set<int> accept[2];
vector<map<char, int>> go[2];

using Pair = pair<int, int>;
map<Pair, bool> used;

bool bfs() {
    queue<Pair> q;
    q.emplace(1, 1);

    while (!q.empty()) {
        auto [u, v] = q.front();
        q.pop();
        if (accept[0].count(u) != accept[1].count(v)) {
            return false;
        }
        used[{u, v}] = true;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            int u_to = go[0][u][ch];
            int v_to = go[1][v][ch];
            if (!used[{u_to, v_to}]) {
                q.emplace(u_to, v_to);
            }
        }
    }
    return true;
}

void solve() {
    for (int t = 0; t < 2; ++t) {
        int n, m, k;
        cin >> n >> m >> k;

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

    cout << (bfs() ? "YES" : "NO");
}

int main() {
    string file = "equivalence";
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
