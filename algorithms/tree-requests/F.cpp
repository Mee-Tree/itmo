#include <iostream>
#include <vector>
#include <map>
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

class LinkCutTree {
    struct Node {
        Node * left = nullptr;
        Node * right = nullptr;
        Node * parent = nullptr;

        int number = 1;
        int cnt = 1;

        Node() = default;

        explicit Node(int index)
            : number(index) {}

        friend bool is_root(Node * node){
            return node && (!node->parent ||
                    (node->parent->left != node && node != node->parent->right));
        }
    };

    typedef Node* Ptr;
    vector<Ptr> nodes;

    int count(Ptr node) const {
        return node ? node->cnt : 0;
    }

    void update(Ptr node) {
        if (!node) return;
        node->cnt = 1 + count(node->left) + count(node->right);
    }

    void rotate(Ptr node) {
        auto parent = node->parent;
        auto grand = parent->parent;
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
            if (parent->left) parent->left->parent = parent;
        } else {
            parent->right = node->left;
            node->left = parent;
            if (parent->right) parent->right->parent = parent;
        }
        parent->parent = node;
        node->parent = grand;
        update(parent);
        update(node);
        update(grand);
    }

    Ptr splay(Ptr node) {
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
        update(node);
        return node;
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

    Ptr get_root(Ptr node) {
        while (!is_root(node)) {
            node = node->parent;
        }
        return node;
    }

    void link(Ptr first, Ptr second) {
        expose(first);
        first->parent = second;
    }

    Ptr lca(Ptr first, Ptr second) {
        expose(first);
        return expose(second);
    }

    int get_index(Ptr node) {
        if (!node) return 0;
        int res = count(node->left);
        for (;!is_root(node); node = node->parent) {
            if (node == node->parent->right) {
                res += count(node->parent->left) + 1;
            }
        }
        return res;
    }

public:
    LinkCutTree(int size) : nodes(size) {
        for (int u = 1; u < size; ++u) {
            nodes[u] = new Node(u);
        }
    }

    void link(int u, int v) {
        link(nodes[u], nodes[v]);
    }

    bool connected(int u, int v) {
        expose(nodes[u]);
        expose(nodes[v]);
        return u == v || nodes[u]->parent;
    }

    int lca(int u, int v) {
        return lca(nodes[u], nodes[v])->number;
    }

    int query(const vector<int> & v) {
        int res = 0;
        for (int u : v) expose(nodes[u]);
        for (int u : v) {
            if (get_index(nodes[u]) == 0) {
                res += count(get_root(nodes[u]));
            }
        }
        return res;
    }
};

void solve() {
    int n;
    long long m;
    cin >> n;

    int size = n + 1;
    LinkCutTree lct(size);

    for (int u = 1, v; u <= n && cin >> v; ++u) {
        if (v == -1) continue;
        lct.link(u, v);
    }

    cin >> m;
    vector<int> q;
    long long k;
    map<vector<int>, int> was;
    while (m-- && cin >> k) {
        q.resize(k);
        while (k--) cin >> q[k];
        if (!was.count(q)) {
            was[q] = lct.query(q);
        }
        cout << was[q] << endl;
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
