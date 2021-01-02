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

const int INF = 2e9;
const int MOD = 1e9;

struct Node {
    int rmq, ind;

    int height;

    Node(): rmq(INF), ind(0), height(-1){}
};


ostream& operator<< (ostream &out, const Node &a) {
    out << a.rmq << " " << a.ind + 1;
    return out;
}

class SegmentTree {
    Node* tree;
    int n;

    const Node E = Node();

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].height == E.height) return;

        int mx = (lx + rx) / 2;
        for (int i = 1; i <= 2; ++i) {
            if (tree[2 * x + i].rmq < tree[x].height) {
                tree[2 * x + i].rmq = tree[x].height;
            }
            tree[2 * x + i].height = max(tree[2 * x + i].height, tree[x].height);
        }
        tree[x].height = E.height;
    }

    Node combine(Node a, Node b) {
        Node c;
        if (a.rmq > b.rmq) {
            swap(a, b);
        }
        c.rmq = a.rmq;
        c.ind = a.ind;
        return c;
    }

    Node rmq(int x, int lx, int rx, int l, int r) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return E;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        Node left = rmq(2 * x + 1, lx, mx, l, r);
        Node right = rmq(2 * x + 2, mx, rx, l, r);
        return combine(left, right);
    }

    void update(int x, int lx, int rx, int l, int r, int height) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return;
        }
        if (lx >= l && rx <= r) {
            if (height != E.height) {
                tree[x].height = height;
                tree[x].rmq = max(tree[x].rmq, height);
            }
            return;
        }
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, height);
        update(2 * x + 2, mx, rx, l, r, height);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x].rmq = 0;
            tree[x].ind = lx;
            tree[x].height = -1;
            return;
        }
        int mx = (lx + rx) / 2;
        build(2 * x + 1, lx, mx);
        build(2 * x + 2, mx, rx);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
public:
    explicit SegmentTree(int sz) {
        n = sz;
        tree = new Node[4 * n];
        build(0, 0, n);
    }

    Node rmq(int l, int r) {
        return rmq(0, 0, n, l, r);
    }

    void update(int l, int r, int val) {
        update(0, 0, n, l, r, val);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTree tree(n);
    for (int i = 0; i < m; ++i) {
        string cmd;
        int left, right, height;
        cin >> cmd;
        cin >> left >> right;
        if (cmd == "defend") {
            cin >> height;
            tree.update(--left, right, height);
        } else {
            cout << tree.rmq(--left, right) << "\n";
        }
    }

    return 0;
}