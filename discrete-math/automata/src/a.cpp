#include <bits/stdc++.h>

using namespace std;

void solve() {
    string word;
    int n, m, k;
    cin >> word >> n >> m >> k;

    set<int> accept;
    for (int i = 0, state; i < k; ++i) {
        cin >> state;
        accept.insert(state);
    }

    vector<map<char, int>> go(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        char sym;
        cin >> u >> v >> sym;
        go[u][sym] = v;
    }

    int state = 1;
    for (char ch : word) {
        state = go[state][ch];
    }

    cout << (accept.count(state) ? "Accepts" : "Rejects");
}

int main() {
#ifndef LOCAL
    string file = "problem1";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
