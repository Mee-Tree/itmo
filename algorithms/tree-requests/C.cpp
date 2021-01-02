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

const int INF = 2e9;

#define ff first
#define ss second
using Pair = pair<int, int>;

void solve() {
    int n, m;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vector<vector<Pair>> dp(n + 1, vector<Pair>(log2(n) + 1, {0, INF}));
    dp[1] = vector<Pair>(log2(n) + 1, {1, INF});
    for (int i = 2, u, c; i <= n; ++i) {
        cin >> u >> c;
        children[u].push_back(i);
        dp[i][0] = {u, c};
    }

    int t = 0;
    vector<int> depth(n + 1);
    vector<int> tin(n + 1), tout(n + 1);
    function<void(int, int)> dfs = [&](int u, int d) {
        tin[u] = t++;
        depth[u] = d;
        for (int i = 1; i < dp[u].size(); ++i) {
            dp[u][i].ff = dp[dp[u][i - 1].ff][i - 1].ff;
            dp[u][i].ss = min(dp[u][i - 1].ss, dp[dp[u][i - 1].ff][i - 1].ss);
        }
        for (int to : children[u]) dfs(to, d + 1);
        tout[u] = t++;
    };
    dfs(1, 0);

    auto minonpath = [&](int u, int v) {
       if (depth[u] > depth[v]) swap(u, v);

       int res = INF;
       int delta = depth[v] - depth[u];
       for (int i = dp[u].size() - 1; i >= 0 && delta; --i) {
           if ((1 << i) <= delta) {
               delta -= (1 << i);
               res = min(res, dp[v][i].ss);
               v = dp[v][i].ff;
           }
       }
       if (u == v) return res;

       for (int i = dp[u].size() - 1; i >= 0; --i) {
           if (dp[u][i].ff != dp[v][i].ff) {
               res = min(res, dp[u][i].ss);
               u = dp[u][i].ff;
               res = min(res, dp[v][i].ss);
               v = dp[v][i].ff;
           }
       }
       return min({res, dp[u][0].ss, dp[v][0].ss});
    };

    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << minonpath(u, v) << endl;
    }
}

int main() {
#ifdef LOCAL
    const string FILENAME = "req";
#else
    const string FILENAME = "minonpath";
#endif
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
