#include <iostream>
#include <vector>
#include <set>
#pragma GCC optimize("-Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("arch=corei7-avx")

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

vector<set<int>> g;

int cur_size;
vector<int> size_;
int find_centroid(int u, int p = 0) {
    for (int to : g[u]) {
        if (to != p && size_[to] > cur_size / 2) {
            return find_centroid(to, u);
        }
    }
    return u;
}

void update_size(int u, int p = 0) {
    size_[u] = 1;
    for (int to : g[u]) {
        if (to == p) continue;
        update_size(to, u);
        size_[u] += size_[to];
    }
}

vector<int> parent;
void decompose(int u, int p = 0) {
    update_size(u);
    cur_size = size_[u];
    int centroid = find_centroid(u);
    parent[centroid - 1] = p;
    for (int to : g[centroid]) {
        g[to].erase(centroid);
        decompose(to, centroid);
    }
}

void solve() {
    int n;
    cin >> n;

    g.resize(n + 1);
    parent.resize(n);
    size_.resize(n + 1);
    for (int _ = 1, u, v; _ < n; ++_) {
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }

    decompose(1);
    for (int p : parent) {
        cout << p << " ";
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
