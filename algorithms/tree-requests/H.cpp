#include <iostream>
#include <vector>
#include <map>
#include <random>

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

const int INF = 2e9;
mt19937 rng((uint64_t) new char);

class EulerTourTree {
    using Edge = pair<int, int>;
    struct Node {
        Node * left = nullptr;
        Node * right = nullptr;
        Node * parent = nullptr;

        Edge edge;
        int cnt = 1;
        int priority;

        Node() = default;

        Node(int u, int v)
            : edge(u, v), priority(rng()) {}
    };

    using Ptr = Node*;
    map<Edge, Ptr> edges;

    int count(Ptr node) const {
        return node ? node->cnt : 0;
    }

    void update(Ptr node) {
        if (!node) return;
        node->cnt = 1 + count(node->left) + count(node->right);
        if (node->left) {
            node->left->parent = node;
        }
        if (node->right) {
            node->right->parent = node;
        }
    }

    Ptr get_root(Ptr node) {
        while (node && node->parent) {
            node = node->parent;
        }
        return node;
    }

    Ptr merge(Ptr left, Ptr right) {
        if (!left) return right;
        if (!right) return left;
        if (left->priority < right->priority) {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
        left->right = merge(left->right, right);
        update(left);
        return left;
    }

    void split(Ptr node, int k, Ptr &left, Ptr &right) {
        if (!node) {
            left = nullptr;
            right = nullptr;
            return;
        }
        int cnt = count(node->left);
        if (cnt < k) {
            split(node->right, k - 1 - count(node->left), node->right, right);
            left = node;
        } else {
            split(node->left, k, left, node->left);
            right = node;
        }
        update(node);
        if (left) left->parent = nullptr;
        if (right) right->parent = nullptr;
    }

    int get_index(Ptr node) {
        if (!node) return 0;
        int res = count(node->left);
        for (;node->parent; node = node->parent) {
            if (node == node->parent->right) {
                res += count(node->parent->left) + 1;
            }
        }
        return res;
    }

public:
    EulerTourTree(int size) {
        for (int u = 1; u < size; ++u) {
            edges[Edge(u, u)] = new Node(u, u);
        }
    }

    void link(int u, int v) {
        auto ff = edges[Edge(u, u)];
        auto ss = edges[Edge(v, v)];

        Ptr a, b, c, d;
        split(get_root(ff), get_index(ff) + 1, a, b);
        split(get_root(ss), get_index(ss), c, d);

        auto uv = new Node(u, v);
        auto vu = new Node(v, u);

        edges[Edge(u, v)] = uv;
        edges[Edge(v, u)] = vu;

        merge(merge(merge(a, uv), d),
              merge(c, merge(vu, b)));
    }

    void cut(int u, int v) {
        Edge e(u, v), re(v, u);
        auto uv = edges[e];
        auto vu = edges[re];
        edges.erase(e);
        edges.erase(re);

        if (get_index(vu) < get_index(uv)) {
            swap(uv, vu);
        }

        Ptr a, bc, c, _;
        split(get_root(uv), get_index(uv), a, bc);
        split(bc, 1, _, bc);
        split(bc, get_index(vu), _, c);
        split(c, 1, _, c);
        merge(a, c);
    }

    bool connected(int u, int v) {
        return get_root(edges[{u, u}])
            == get_root(edges[{v, v}]);
    }

};

void solve() {
    int n, m;
    cin >> n >> m;

    EulerTourTree ett(n + 1);
    for (string cmd; m-- && cin >> cmd;) {
        int u, v;
        cin >> u >> v;
        if (cmd == "link") {
            ett.link(u, v);
        } else if (cmd == "cut") {
            ett.cut(u, v);
        } else {
            cout << ett.connected(u, v) << endl;
        }
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