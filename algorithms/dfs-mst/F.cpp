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

vector<vector<int>> g, rg;
vector<int> colour;
vector<bool> used;
vector<int> top;
int clr = 1;

void dfs1(int u) {
    used[u] = true;
    for (int to : g[u]) {
        if (!used[to]) { dfs1(to); }
    }
    top.emplace_back(u);
}

void dfs2(int u) {
    colour[u] = clr;
    for (int to : rg[u]) {
        if (!colour[to]) { dfs2(to); }
    }
}

void resize(int sz) {
    g.resize(sz);
    rg.resize(sz);
    used.resize(sz);
    colour.resize(sz);
}

void solve() {
    int n, m;
    cin >> n >> m;

    resize(n + 1);
    for (int u, v; m-- && cin >> u >> v;) {
        g[u].emplace_back(v);
        rg[v].emplace_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!used[i]) { dfs1(i); }
    }

    reverse(top.begin(), top.end());
    for (int i : top) {
        if (!colour[i]) {
            dfs2(i);
            ++clr;
        }
    }

    set<pair<int, int>> diff;
    for (int i = 1; i <= n; ++i) {
        for (int to : g[i]) {
            if (colour[i] != colour[to]) {
                diff.emplace(colour[i], colour[to]);
            }
        }
    }

    cout << diff.size();
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


