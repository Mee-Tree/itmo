#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
using graph = vector<vector<int>>;

graph decode(vector<int>& prufer) {
    int n = (int) prufer.size() + 2;
    vector<int> degree(n, 1);

    set<int> leaves;
    for (int u : prufer) { ++degree[u]; }
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) { leaves.insert(i); }
    }

    graph result(n);
    for (int u : prufer) {
        result[*leaves.begin()].emplace_back(u);
        leaves.erase(leaves.begin());

        if (--degree[u] == 1) {
            leaves.insert(u);
        }
    }

    assert(leaves.size() == 2);
    result[*leaves.begin()].emplace_back(*leaves.rbegin());
    return result;
}

void solve() {
    int n;
    cin >> n;

    vector<int> prufer(n - 2);
    for (int i = 0; i < n - 2; ++i) {
        cin >> prufer[i];
        --prufer[i];
    }

    const graph& g = decode(prufer);
    for (int u = 0; u < g.size(); ++u) {
        for (int to : g[u]) {
            cout << u + 1 << " " << to + 1 << endl;
        }
    }
}

int main() {
    const string FILE = "local";
#ifdef LOCAL
    freopen((FILE + ".in").c_str(), "r", stdin);
    freopen((FILE + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
