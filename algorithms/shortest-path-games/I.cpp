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

const ll INF = 1e18 + 1337;

namespace {

enum result {
    WIN, LOSE, DRAW
};

ostream& operator << (ostream& out, const result& r) {
    static string mp[]{ "FIRST", "SECOND", "DRAW" };
    return out << mp[r];
}

vector<bool> used;
vector<int> degree;
vector<vector<int>> g;
vector<vector<int>> rg;
vector<result> results;

void dfs(int u) {
    used[u] = true;
    for (int to : rg[u]) {
        if (used[to]) { continue; }
        if (results[u] == LOSE) {
            results[to] = WIN;
        } else if (!--degree[to]) {
            results[to] = LOSE;
        } else { continue; }
        dfs(to);
    }
}

void solve(int n, int m) {
    g.assign(n + 1, vector<int>());
    rg.assign(n + 1, vector<int>());
    degree.assign(n + 1, 0);
    used.assign(n + 1, false);
    results.assign(n + 1, DRAW);

    for (int u, v; m-- && cin >> u >> v;) {
        g[u].emplace_back(v);
        rg[v].emplace_back(u);
        ++degree[u];
    }

    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) {
            results[i] = LOSE;
            dfs(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << results[i] << endl;
    }
    cout << endl;
}

} // anonymous

signed main() {
#ifdef LOCAL
    const string FILENAME = "local";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    while (cin >> n >> m) { solve(n, m); }
    return 0;
}


