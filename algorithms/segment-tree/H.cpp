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

const int INF = INT_MAX;
const int MOD = 1e9;

struct Node {
    int val;
    int set;

    Node(): val(INF), set(INF){}
};


class SegmentTree {
    Node* tree;
    int n;

    const Node E = Node();

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].set == E.set) return;

        int mx = (lx + rx) / 2;
        for (int i = 1; i <= 2; ++i) {
            if (tree[x].set != E.set) {
                tree[2 * x + i].set = tree[x].set;
                tree[2 * x + i].val = tree[x].set;
            }
        }
        tree[x].set = E.set;
    }

    Node combine(Node a, Node b) {
        Node c;
        c.val = min(a.val, b.val);
        return c;
    }

    Node rmq(int x, int lx, int rx, int l, int r) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return E;
        }
        if (l <= lx && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        Node left = rmq(2 * x + 1, lx, mx, l, r);
        Node right = rmq(2 * x + 2, mx, rx, l, r);
        return combine(left, right);
    }

    void update(int x, int lx, int rx, int l, int r, int val) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            if (val != E.set) {
                tree[x].set = val;
                tree[x].val = val;
            }
            return;
        }
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, val);
        update(2 * x + 2, mx, rx, l, r, val);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
public:
    explicit SegmentTree(int sz) {
        n = sz;
        tree = new Node[4 * n];
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

struct Query {
    int left;
    int right;
    int value;

    Query() = default;

    Query(int left, int right, int value): left(left), right(right), value(value) {}
};

signed main() {
    string FILENAME = "rmq";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Query> q(m);
    for (int i = 0; i < m; ++i) {
        int left, right, val;
        cin >> left >> right >> val;
        q[i] = Query(--left, right, val);
    }
    sort(q.begin(), q.end(), [](Query a, Query b) {
        return a.value < b.value;
    });

    SegmentTree tree(n);
    for (int i = 0; i < m; ++i) {
        tree.update(q[i].left, q[i].right, q[i].value);
    }

    for (int i = 0; i < m; ++i) {
        if (tree.rmq(q[i].left, q[i].right).val != q[i].value) {
            cout << "inconsistent";
            return 0;
        }
    }

    cout << "consistent\n";
    for (int i = 0; i < n; ++i) {
        cout << tree.rmq(i, i + 1).val << " ";
    }
    return 0;
}