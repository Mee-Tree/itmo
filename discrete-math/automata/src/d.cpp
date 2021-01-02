#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    set<int> accept;
    for (int i = 0, state; i < k; ++i) {
        cin >> state;
        accept.insert(state);
    }

    vector<map<char, int>> go(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        char sym;
        cin >> u >> v >> sym;
        go[u][sym] = v;
    }

    vector<vector<int>> dp(l + 1, vector<int>(n + 1));
    dp[0][1] = 1;
    for (int i = 1; i <= l; ++i) {
        for (int u = 1; u <= n; ++u) {
            for (auto [ch, to] : go[u]) {
                dp[i][to] += dp[i - 1][u];
                dp[i][to] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int u : accept) {
        ans = (ans + dp[l][u]) % MOD;
    }

    cout << ans;
}

int main() {
#ifndef LOCAL
    string file = "problem4";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
