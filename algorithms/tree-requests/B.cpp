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

void solve() {
    int n, m;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(log2(n) + 1));
    dp[1] = vector<int>(log2(n) + 1, 1);
    for (int i = 2, u; i <= n; ++i) {
        cin >> u;
        children[u].push_back(i);
        dp[i][0] = u;
    }

    int t = 0;
    vector<int> tin(n + 1), tout(n + 1);
    function<void(int)> dfs = [&](int u) {
        tin[u] = t++;
        for (int i = 1; i < dp[u].size(); ++i) {
            dp[u][i] = dp[dp[u][i - 1]][i - 1];
        }
        for (int to : children[u]) dfs(to);
        tout[u] = t++;
    };
    dfs(1);

    auto ancest = [&](int u, int v) {
        return tin[u] <= tin[v]
            && tout[v] <= tout[u];
    };

    auto lca = [&](int u, int v) {
        if (ancest(u, v)) return u;
        if (ancest(v, u)) return v;
        for (int i = dp[v].size() - 1; i >= 0; --i) {
            if (!ancest(dp[u][i], v)) u = dp[u][i];
        }
        return dp[u][0];
    };

    cin >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << endl;
    }
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
