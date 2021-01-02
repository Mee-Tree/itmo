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
vector<int> colour;

void paint(int u) {
    int last = 0; ++colour;
    while (last != u && !st.empty()) {
        last = st.top();
        st.pop();
        colour[last - 1] = colour;
    }
}

void dfs(int u, int p = -1) {
    used[u] = true;
    st.push(u);
    tin[u] = up[u] = t++;
    for (auto [to, ind] : g[u]) {
        if (ind == p) { continue; }
        if (used[to]) {
            up[u] = min(up[u], tin[to]);
        } else {
            dfs(to, ind);
            up[u] = min(up[u], up[to]);
            if (up[to] > tin[u]) {
                paint(to);
            }
        }
    }
}

void resize(int sz) {
    g.resize(sz);
    used.resize(sz);
    up.resize(sz);
    tin.resize(sz);
    colour.resize(sz - 1);
}

void solve() {
    int n, m;
    cin >> n >> m;

    resize(n + 1);
    for (int i = 1, u, v; i <= m && cin >> u >> v; ++i) {
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int u = 1; u <= n; ++u) {
        if (!used[u]) {
            dfs(u);
            int last; ++colour;
            while (!st.empty()) {
                last = st.top();
                st.pop();
                colour[last - 1] = colour;
            }
        }
    }

    cout << colour << endl;
    for (int u : colour) {
        cout << u << " ";
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


