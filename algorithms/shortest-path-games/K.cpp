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
using ull = unsigned long long;
using pii = pair<int, int>;
using pill = pair<int, ll>;

const ll INF = 1e18 + 1337;

vector<bool> used;
vector<int> size_;
vector<ull> grundy;
vector<vector<int>> g;
map<set<int>, int> num;

int calc_size(int u) {
    used[u] = true;
    size_[u] = 1;
    for (int to : g[u]) {
        if (used[to]) { continue; }
        size_[u] += calc_size(to);
    }
    return size_[u];
}

ull find_ans(int u) {
    used[u] = true;
    ull gr = 0;
    for (int to : g[u]) {
        if (used[to]) { continue; }
        ull gr_sub = find_ans(to);
        gr ^= (gr_sub + 1);
    }

    return grundy[u] = gr;
}

void find_win_move(int u, ull xr) {
    used[u] = true;
    ull gr = grundy[u] ^ xr;

    for (int to : g[u]) {
        if (!used[to] && !(gr ^ (grundy[to] + 1))) {
            cout << num[{u, to}];
            exit(0);
        }
    }

    for (int to : g[u]) {
        if (used[to]) { continue; }
        ull new_xr = gr ^ (grundy[to] + 1);
        find_win_move(to, new_xr - 1);
    }
}

void solve() {
    int n, r;
    cin >> n >> r;

    g.resize(n + 1);
    used.resize(n + 1);
    size_.resize(n + 1);
    grundy.resize(n + 1);

    for (int u, v, i = 1; i < n
            && cin >> u >> v; ++i) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
        num[{u, v}] = i;
    }

    calc_size(r);
    used.assign(n + 1, false);
    ull ans = find_ans(r) == 0 ? 2 : 1;
    cout << ans << endl;

    if (ans == 1) {
        used.assign(n + 1, false);
        find_win_move(r, 0);
    }
}

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


