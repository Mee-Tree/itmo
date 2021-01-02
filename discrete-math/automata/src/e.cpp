#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

vector<map<char, int>> go(101);
set<int> accept;

void to_DFA(vector<map<char, vector<int>>> & NFA,
            set<int> & NFA_accept) {
    queue<set<int>> states;
    states.push({1});

    int num = 1;
    map<set<int>, int> assoc;
    assoc[{1}] = num++;
    if (NFA_accept.count(1)) {
        accept.insert(1);
    }
    while (!states.empty()) {
        auto state = states.front();
        states.pop();

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            set<int> nw;
            bool accepts = false;
            for (int s : state) {
                for (int to : NFA[s][ch]) {
                    nw.insert(to);
                    if (NFA_accept.count(to)) {
                        accepts = true;
                    }
                }
            }

            if (!assoc.count(nw)) {
                if (accepts) accept.insert(num);
                assoc[nw] = num++;
                states.push(nw);
            }
            go[assoc[state]][ch] = assoc[nw];
        }
    }
}

void solve() {
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    set<int> NFA_accept;
    for (int i = 0, state; i < k; ++i) {
        cin >> state;
        NFA_accept.insert(state);
    }

    vector<map<char, vector<int>>> NFA(n + 1);
    for (int i = 0, u, v; i < m; ++i) {
        char sym;
        cin >> u >> v >> sym;
        NFA[u][sym].push_back(v);
    }

    to_DFA(NFA, NFA_accept);

    vector<vector<int>> cnt(l + 1, vector<int>(go.size()));
    cnt[0][1] = 1;
    for (int i = 1; i <= l; ++i) {
        for (int u = 1; u < go.size(); ++u) {
            for (auto [ch, to] : go[u]) {
                cnt[i][to] += cnt[i - 1][u];
                cnt[i][to] %= MOD;
            }
        }
    }

    int ans = 0;
    for (int u : accept) {
        ans = (ans + cnt[l][u]) % MOD;
    }

    cout << ans;
}

int main() {
    string file = "problem5";
#ifndef LOCAL
    freopen((file + ".out").c_str(), "w", stdout);
    freopen((file + ".in").c_str(), "r", stdin);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
