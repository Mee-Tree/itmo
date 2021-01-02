#include <bits/stdc++.h>

#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

struct edge {
    int u, v;

    edge(int u, int v)
        : u(min(u, v)), v(max(u, v)) {}

    bool operator < (edge other) const {
        return u < other.u
            || u == other.u && v < other.v;
    }
};

set<edge> remove(set<edge> edges) {
    edges.erase(edges.begin());
    return edges;
}

set<edge> merge(const set<edge>& edges) {
    set<edge> new_edges;
    auto [u, v] = *edges.begin();
    for (const edge& e : remove(edges)) {
        new_edges.emplace(e.u == u ? v : e.u,
                          e.v == u ? v : e.v);
    }
    return new_edges;
}

ll get_last(vector<ll>& v, ll def = 0) {
    ll last = def;
    if (!v.empty()) {
        last = v.back();
        v.pop_back();
    }
    return last;
}

vector<ll> get_poly(const set<edge>& edges, int n) {
    if (edges.empty()) {
        vector<ll> vv(n + 1);
        vv.front() = 1;
        return vv;
    }

    // p(g, k) = p(g - uv, k) - p(g/uv, k)
    auto first = get_poly(remove(edges), n);
    auto second = get_poly(merge(edges), n - 1);
    vector<ll> result(n + 1);
    for (int i = (int) result.size() - 1; i >= 0; --i) {
        result[i] = get_last(first) - get_last(second);
    }
    return result;
}

void solve() {
    int n, m;
    cin >> n >> m;

    set<edge> edges;
    for (int u, v; m-- && cin >> u >> v;) {
        edges.emplace(--u, --v);
    }

    const vector<ll>& poly = get_poly(edges, n);
    cout << poly.size() - 1 << endl;
    for (int x : poly) {
        cout << x << " ";
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