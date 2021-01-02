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

vector<vector<pair<int, int>>> g;
vector<bool> used;
vector<int> tin, up;
int t = 0;

int colour = 0;
stack<int> st;
vector<int> colours;

void paint(int u, int p, int cl) {
    used[u] = true;
    for (auto [to, ind] : g[u]) {
        if (ind == p) { continue; }
        if (!used[to]) {
            int clr = cl;
            if (up[to] >= tin[u]) {
                clr = ++colour;
            }
            colours[ind] = clr;
            paint(to, ind, clr);
        } else if (tin[to] < tin[u]) {
            colours[ind] = cl;
        }
    }
}

void dfs(int u, int p = -1) {
    used[u] = true;
    tin[u] = up[u] = t++;
    for (auto [to, ind] : g[u]) {
        if (ind == p) { continue; }
        if (used[to]) {
            up[u] = min(up[u], tin[to]);
        } else {
            dfs(to, ind);
            up[u] = min(up[u], up[to]);
        }
    }
}

void resize(int sz) {
    g.resize(sz);
    used.resize(sz);
    up.resize(sz);
    tin.resize(sz);
}

void solve() {
    int n, m;
    cin >> n >> m;

    resize(n + 1);
    colours.resize(m);
    for (int i = 0, u, v; i < m && cin >> u >> v; ++i) {
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int u = 1; u <= n; ++u) {
        if (!used[u]) { dfs(u); }
    }
    used.assign(n + 1, false);
    for (int u = 1; u <= n; ++u) {
        if (!used[u]) {
            paint(u, -1, ++colour);
        }
    }

    int clr = 0;
    unordered_map<int, int> mp;
    for (int u : colours) {
        if (!mp[u]) { mp[u] = ++clr; }
    }

    cout << clr << endl;
    for (int u : colours) {
        cout << mp[u] << " ";
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


