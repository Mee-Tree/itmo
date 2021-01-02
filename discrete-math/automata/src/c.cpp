#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

set<int> accept;
vector<vector<int>> go;
vector<vector<int>> rev;
vector<bool> used;

bool cycle_check() {
    vector<bool> visited(used.size());
    std::function<void(int)> visit = [&](int u) {
        visited[u] = true;
        for (auto to : rev[u]) {
            if (!visited[to]) visit(to);
        }
    };

    for (auto u : accept) visit(u);

    vector<char> color(used.size());
    std::function<bool(int)> check = [&](int u) {
        color[u] = 1;
        for (auto to : go[u]) {
            if (visited[to] &&
                (color[to] == 1 || color[to] == 0 && check(to))) {
                return true;
            }
        }
        color[u] = 2;
        return false;
    };
    return check(1);
}

void dfs(int u, vector<int> & v) {
    used[u] = true;
    for (int to : go[u]) {
        if (!used[to]) {
            dfs(to, v);
        }
    }
    v.push_back(u);
}

auto top_sort() {
    vector<int> v;
    for (int i = 1; i < go.size(); ++i) {
        if (!used[i]) {
            dfs(i, v);
        }
    }
    reverse(v.begin(), v.end());
    return v;
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 0, state; i < k; ++i) {
        cin >> state;
        accept.insert(state);
    }

    go.resize(n + 1);
    rev.resize(n + 1);
    used.resize(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        char sym;
        cin >> u >> v >> sym;
        go[u].push_back(v);
        rev[v].push_back(u);
    }

    if (cycle_check()) {
        cout << -1;
        return;
    }

    vector<int> dp(n + 1);
    dp[1] = 1;
    for (int u : top_sort()) {
        for (int from : rev[u]) {
            dp[u] += dp[from];
            dp[u] %= MOD;
        }
    }

    int ans = 0;
    for (int a : accept) {
        ans += dp[a];
        ans %= MOD;
    }
    cout << ans;
}

int main() {
#ifndef LOCAL
    string file = "problem3";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
