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
using vvpii = vector<vector<pair<int, int>>>;

vvpii g, rg;
vector<bool> used;

void dfs(int u, int lmt, const vvpii & gg) {
    used[u] = true;
    for (auto [to, w] : gg[u]) {
        if (!used[to] && w <= lmt) {
            dfs(to, lmt, gg);
        }
    }
}

auto identity = [](auto x) { return x; };

auto every = [](auto v) -> bool {
    return all_of(v.begin(), v.end(), identity);
};

bool check(int lmt) {
    bool ok = true;
    for (const auto& gg : {g, rg}) {
        used.assign(used.size(), false);
        dfs(0, lmt, gg);
        ok &= every(used);
    }
    return ok;
}

void solve() {
    int n, mx = -1;
    cin >> n;

    g.resize(n);
    rg.resize(n);
    used.resize(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w; cin >> w;
            g[i].emplace_back(j, w);
            rg[j].emplace_back(i, w);
            mx = max(mx, w);
        }
    }

    int left = 0, right = mx;
    while (left + 1 < right) {
        int mid = (left + right) / 2;

        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << right;
}

int main() {
    string FILENAME = "avia";
#ifdef LOCAL
    FILENAME = "req";
#endif
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}


