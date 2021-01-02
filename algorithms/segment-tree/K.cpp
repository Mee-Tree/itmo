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
    int val;
    int left;
    int right;

    Node(): val(0), left(INF), right(INF) {}

    Node(int val, int left, int right): val(val), left(left), right(right) {}
};

ostream& operator<< (ostream &out, const Node &a) {
    out << a.val;
    return out;
}

class SegmentTree {
    Node* tree;
    int n;

    const Node E = Node();

    Node combine(Node a, Node b) {
        Node c;
        c.left = min(a.left, b.left);
        c.right = min(b.right, a.right);
        return c;
    }

    Node find(int x, int lx, int rx, int l, int r) {
        if (rx <= l || lx >= r) {
            return E;
        }
        if (l <= lx && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        Node left = find(2 * x + 1, lx, mx, l, r);
        Node right = find(2 * x + 2, mx, rx, l, r);
        return combine(left, right);
    }

    void update(int x, int lx, int rx, int ind, int val) {
        if (rx - lx == 1) {
            if (val == 1) {
                ind = INF;
            }
            tree[x] = Node(val, ind, ind);
            return;
        }
        int mx = (lx + rx) / 2;
        if (ind < mx) {
            update(2 * x + 1, lx, mx, ind, val);
        } else {
            update(2 * x + 2, mx, rx, ind, val);
        }
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x].val = 0;
            tree[x].left = lx;
            tree[x].right = lx;
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

    Node find(int l, int r) {
        return find(0, 0, n, l, r);
    }

    void update(int ind, int val) {
        update(0, 0, n, ind, val);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

signed main() {
    string FILENAME = "parking";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;

    SegmentTree tree(n);
    for (int i = 0; i < m; ++i) {
        string cmd;
        int num;
        cin >> cmd;
        cin >> num;

        if (cmd == "enter") {
            int l = tree.find(0, num).left;
            int r = tree.find(num - 1, n).right;
            int ans = (r <= n + l ? r : l) + 1;
            cout << ans << "\n";
            tree.update(ans - 1, 1);
        } else {
            tree.update(num - 1, 0);
        }
    }

    return 0;
}