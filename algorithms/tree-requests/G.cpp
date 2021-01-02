#include <iostream>
#include <vector>
#include <map>
#include <functional>

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
using ll = long long;

const int INF = 2e9;

class LinkCutTree {
    struct Node {
        Node * left = nullptr;
        Node * right = nullptr;
        Node * parent = nullptr;

        ll d = 0L;
        ll num = 0L;
        int cnt = 1;

        friend bool is_root(Node * node){
            return node && (!node->parent
                            || (node->parent->left != node && node != node->parent->right));
        }
    };

    using Ptr = Node *;
    vector<Ptr> nodes;

    int count(Ptr node) const {
        return node ? node->cnt : 0;
    }

    void add(Ptr node, ll d) {
        if (!node) return;
        node->num += d;
        node->d += d;
    }

    void propagate(Ptr node) {
        if (!node) return;
        add(node->left, node->d);
        add(node->right, node->d);
        node->d = 0L;
    }

    void update(Ptr node) {
        if (!node) return;
        node->cnt = 1 + count(node->left) + count(node->right);
    }

    void update_parent(Ptr node) {
        if (!node) return;
        if (node->left) node->left->parent = node;
        if (node->right) node->right->parent = node;
    }

    void rotate(Ptr node) {
        auto parent = node->parent;
        auto grand = parent->parent;
        propagate(grand); propagate(parent); propagate(node);
        if (!is_root(parent)) {
            if (grand->left == parent) {
                grand->left = node;
            } else {
                grand->right = node;
            }
        }
        if (parent->left == node) {
            parent->left = node->right;
            node->right = parent;
        } else {
            parent->right = node->left;
            node->left = parent;
        }
        update_parent(node); update_parent(parent);
        node->parent = grand;
        update(parent); update(node); update(grand);
    }

    void splay(Ptr node) {
        while (!is_root(node)) {
            auto parent = node->parent;
            auto grand = parent->parent;
            if (!is_root(parent)) {
                if ((grand->left == parent) == (parent->left == node)) {
                    rotate(parent); // zig-zig
                } else rotate(node); // zig-zag
            }
            rotate(node); // zig
        }
        propagate(node);
        update(node);
    }

    Ptr expose(Ptr node) {
        Ptr last = nullptr;
        for (Ptr u = node; u; u = u->parent) {
            splay(u);
            u->left = last;
            update(u);
            last = u;
        }
        splay(node);
        return last;
    }

    Ptr lca(Ptr u, Ptr v) {
        expose(u);
        return expose(v);
    }

public:
    LinkCutTree(int size) : nodes(size) {
        for (int u = 1; u < size; ++u) {
            nodes[u] = new Node();
        }
    }

    void build(vector<vector<int>> & g) {
        vector<bool> used(g.size());
        auto dfs = [&](int u, const auto& dfs) -> void {
            used[u] = true;
            for (int to : g[u]) {
                if (!used[to]) {
                    link(u, to);
                    dfs(to, dfs);
                }
            }
        }; dfs(1, dfs);
    }

    void link(int u, int v) {
        expose(nodes[v]);
        nodes[v]->parent = nodes[u];
    }

    void add(int u, int v, ll d) {
        Ptr first = nodes[u];
        Ptr second = nodes[v];
        Ptr _lca = lca(first, second);
        if (first != _lca && second != _lca) {
            splay(first);
            add(first, d);
        } else if (first == _lca) {
            expose(second);
        } else expose(first);
        splay(_lca);
        add(_lca->left, d);
        _lca->num += d;
    }

    ll get(int u) {
        splay(nodes[u]);
        return nodes[u]->num;
    }
};

void solve() {
    int n, m;
    scanf("%d", &n);

    LinkCutTree lct(n + 1);
    vector<vector<int>> g(n + 1);
    for (int u, v; --n && scanf("%d %d", &u, &v);) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    lct.build(g);

    scanf("%d", &m);
    for (char cmd; m-- && scanf("\n%c", &cmd);) {
        int u, v; ll d;
        scanf("%d", &u);
        if (cmd == '+') {
            scanf("%d %lld", &v, &d);
            lct.add(u, v, d);
        } else {
            printf("%lld\n", lct.get(u));
        }
    }
}

signed main() {
#ifdef LOCAL
    const string FILENAME = "req";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    solve();
    return 0;
}