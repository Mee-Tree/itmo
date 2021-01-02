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

struct tuple {
    int ff, ss;
    ll tt;

    tuple(int ff, int ss, ll tt)
        : ff(ff), ss(ss), tt(tt) {}
};

void solve() {
    int n;
    cin >> n;

    vector<ll> d(n, 0);
    vector<int> p(n, -1);
    vector<tuple> g;

    for (int i = 0; i < n; ++i) {
        for (int j = 0, w; j < n && cin >> w; ++j) {
            if (w == 1e5) { continue; }
            g.emplace_back(i, j, w);
        }
    }

    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (auto [ff, ss, tt] : g) {
            if (d[ss] > d[ff] + tt) {
                d[ss] = max(d[ff] + tt, -INF);
                p[ss] = ff, x = ss;
            }
        }

        if (x == -1) {
            cout << "NO";
            return;
        }
    }

    cout << "YES" << endl;

    vector<ll> path;
    for (int _ = 0; _ < n; ++_, x = p[x]);
    for (int cur = x; path.empty() || cur != x; cur = p[cur]) {
        path.emplace_back(cur);
    }

    cout << path.size() << endl;
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i] + 1 << " ";
    }
}

} // anonymous

signed main() {
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


