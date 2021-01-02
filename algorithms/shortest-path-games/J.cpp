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

vector<bool> used;
vector<int> grundy;
vector<vector<int>> g;

const int SIZE = (int) 1e5 + 1;
int ver = 0;

int mex(vector<int>& gg) {
    static int us[SIZE] = {0};
    ++ver;
    for (int to : gg) {
        if (grundy[to] < SIZE) {
            us[grundy[to]] = ver;
        }
    }
    for (int i = 0; i <= gg.size(); ++i) {
        if (us[i] != ver) { return i; }
    }
    return 0;
}

void dfs(int u) {
    used[u] = true;
    for (int to : g[u]) {
        if (used[to]) { continue; }
        dfs(to);
    }
    grundy[u] = mex(g[u]);
}

void solve() {
    int n, m;
    cin >> n >> m;

    g.resize(n + 1);
    used.resize(n + 1);
    grundy.resize(n + 1);

    for (int u, v; m-- && cin >> u >> v;) {
        g[u].emplace_back(v);
    }

    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << grundy[i] << endl;
    }
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
    solve();
    return 0;
}


