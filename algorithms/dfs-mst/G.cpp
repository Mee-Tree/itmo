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
using ld = long double;

const int INF = 1e9 + 7;

vector<vector<int>> g, gr;
vector<bool> used;
vector<int> top, comp;

void dfs1(int v) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to])
            dfs1(to);
    }
    top.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int to : gr[v]) {
        if (comp[to] == -1) {
            dfs2(to, cl);
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    g.resize(2 * n);
    gr.resize(2 * n);
    unordered_map<string, int> names;
    vector<string> nums(n);

    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        string name; cin >> name;

        names["+" + name] = cnt;
        names["-" + name] = cnt + 1;

        nums[cnt / 2] = name;
        cnt += 2;
    }

    for (int i = 0; i < m; i++) {
        string uStr, vStr, _;
        cin >> uStr >> _ >> vStr;

        int u = names[uStr];
        int v = names[vStr];

        g[u].push_back(v);
        g[v ^ 1].push_back(u ^ 1);

        gr[v].push_back(u);
        gr[u ^ 1].push_back(v ^ 1);
    }

    used.assign(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        if (!used[i]) { dfs1(i); }
    }

    comp.assign(2 * n, -1);
    for (int i = 0, cl = 0; i < 2 * n; ++i) {
        int v = top[top.size() - i - 1];
        if (comp[v] == -1) {
            dfs2(v, cl++);
        }
    }

    vector<string> ans;
    for (int i = 0; i < 2 * n; i += 2) {
        if (comp[i] == comp[i ^ 1]) {
            cout << -1;
            return;
        } else if (comp[i] > comp[i ^ 1]) {
            ans.push_back(nums[i / 2]);
        }
    }

    cout << ans.size() << endl;
    for (auto& name : ans) {
        cout << name << endl;
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


