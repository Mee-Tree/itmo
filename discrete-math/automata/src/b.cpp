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

    vector<map<char, vector<int>>> go(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        char sym;
        cin >> u >> v >> sym;
        go[u][sym].push_back(v);
    }


    vector<vector<bool>> can(word.length() + 1, vector<bool>(n + 1));
    can[0][1] = true;
    for (int i = 0; i < word.size(); ++i) {
        for (int u = 1; u <= n; ++u) {
            if (!can[i][u]) continue;
            for (int to : go[u][word[i]]) {
                can[i + 1][to] = true;
            }
        }
    }

    for (int u : accept) {
        if (can[word.size()][u]) {
            cout << "Accepts";
            return;
        }
    }

    cout << "Rejects";
}

int main() {
#ifndef LOCAL
    string file = "problem2";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
