#include <bits/stdc++.h>

using namespace std;

set<int> accept;
vector<map<char, int>> go;
vector<vector<int>> rev_go;

set<int> visited;
void rev_dfs(int u) {
    visited.insert(u);
    for (int to : rev_go[u]) {
        if (!visited.count(to)) {
            rev_dfs(to);
        }
    }
}

set<int> good;
void reach(int start) {
    for (int a : accept) {
        rev_dfs(a);
    }
    set<int> used;
    std::function<void(int)> dfs = [&](int u) {
        used.insert(u);
        for (auto [_, to] : go[u]) {
            if (!used.count(to)) {
                dfs(to);
            }
        }
    };
    dfs(start);
    for (int u : used) {
        if (visited.count(u)) {
            good.insert(u);
        }
    }
    used.clear();
    visited.clear();
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    for (int s; k--;) {
        cin >> s;
        accept.insert(s);
    }

    go.resize(n + 1);
    rev_go.resize(n + 1);
    set<char> symbols;
    for (int u, v; m--;) {
        char sym;
        cin >> u >> v >> sym;
        go[u][sym] = v;
        rev_go[v].push_back(u);
        symbols.insert(sym);
    }

    reach(1);
    vector<map<char, vector<int>>> rev_good(n + 1);
    set<int> acc, non_acc;
    map<int, int> cls;
    for (int u : good) {
        for (auto [ch, to] : go[u]) {
            rev_good[to][ch].push_back(u);
        }
        if (accept.count(u)) {
            acc.insert(u);
            cls[u] = 1;
        } else {
            non_acc.insert(u);
            cls[u] = 2;
        }
    }

    vector<set<int>> split(1);
    for (auto & t : {acc, non_acc}) {
        if (!t.empty()) {
            split.push_back(t);
        }
    }

    using Pair = pair<set<int>, char>;
    queue<Pair> q;
    for (char ch : symbols) {
        for (auto & t : {acc, non_acc}) {
            q.emplace(t, ch);
        }
    }

    while (!q.empty()) {
        Pair p = q.front();
        q.pop();
        map<int, set<int>> inv;
        for (int u : p.first) {
            for (int v : rev_good[u][p.second]) {
                inv[cls[v]].insert(v);
            }
        }
        for (auto & [c, s] : inv) {
            if (c >= split.size()) continue;
            if (s.size() < split[c].size()) {
                split.emplace_back();
                for (int r : s) {
                    split[c].erase(r);
                    split.back().insert(r);
                }
                if (split.back().size() > split[c].size()) {
                    swap(split.back(), split[c]);
                }
                for (int r : split.back()) {
                    cls[r] = split.size() - 1;
                }
                for (char ch : symbols) {
                    q.emplace(split.back(), ch);
                }
            }
        }
    }

    int s = cls[1];
    if (s) {
        for (auto & [_, u] : cls) {
            if (u == s) u = 1;
            else if (u == 1) {
                u = s;
            }
        }
    }

    vector<map<char, int>> new_go(split.size());
    set<int> new_accept;
    int new_m = 0;
    for (int u = 1; u <= n; ++u) {
        if (!cls[u]) continue;
        for (auto [ch, v] : go[u]) {
            if (!cls[v] || new_go[cls[u]].count(ch)) continue;
            new_go[cls[u]][ch] = cls[v];
            ++new_m;
        }
        if (accept.count(u)) {
            new_accept.insert(cls[u]);
        }
    }

    cout << new_go.size() - 1 << " " << new_m << " " << new_accept.size() << endl;
    for (int a : new_accept) {
        cout << a << " ";
    }
    for (int u = 1; u < new_go.size(); ++u) {
        for (auto [ch, to] : new_go[u]) {
            cout << endl << u << " " << to << " " << ch;
        }
    }
}

int main() {
    string file = "minimization";
#ifndef LOCAL
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
