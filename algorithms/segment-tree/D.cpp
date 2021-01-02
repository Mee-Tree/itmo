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
    int cnt, len;
    int first, last;

    int set;

    Node(): cnt(0), len(0), first(0), last(0), set(-1){}
};


ostream& operator<< (ostream &out, const Node &a) {
    out << a.cnt << " " << a.len;
    return out;
}

class SegmentTree {
    Node* tree;
    int n;

    const Node E = Node();

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].set == E.set) return;

        int mx = (lx + rx) / 2;
        for (int i = 1; i <= 2; ++i) {
            tree[2 * x + i].cnt = tree[x].set;
            tree[2 * x + i].set = tree[x].set;
            tree[2 * x + i].first = tree[2 * x + i].last = tree[x].set;
        }
        tree[2 * x + 1].len = (mx - lx) * tree[x].set;
        tree[2 * x + 2].len = (rx - mx) * tree[x].set;
        tree[x].set = E.set;
    }

    Node combine(Node a, Node b) {
        Node c;
        c.first = a.first;
        c.last = b.last;
        c.cnt = a.cnt + b.cnt - (a.last && b.first);
        c.len = a.len + b.len;
        return c;
    }

    Node count(int x, int lx, int rx, int l, int r) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return E;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        Node left = count(2 * x + 1, lx, mx, l, r);
        Node right = count(2 * x + 2, mx, rx, l, r);
        return combine(left, right);
    }

    void update(int x, int lx, int rx, int l, int r, int setVal) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return;
        }
        if (lx >= l && rx <= r) {
            if (setVal != E.set) {
                tree[x].set = setVal;
                tree[x].cnt = setVal;
                tree[x].len = (rx - lx) * setVal;
                tree[x].first = tree[x].last = setVal;
            }
            return;
        }
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, setVal);
        update(2 * x + 2, mx, rx, l, r, setVal);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }
public:
    explicit SegmentTree(int sz) {
        n = sz;
        tree = new Node[4 * n];
    }

    Node count() {
        return tree[0];
    }

    void update(int l, int r, int setVal) {
        update(0, 0, n, l, r, setVal);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

struct Query {
    int left;
    int right;
    int color;

    Query() = default;

    Query(int left, int right, int color): left(left), right(right), color(color) {}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    auto* q = new Query[n];
    int L = INF, R = -INF;

    for (int i = 0; i < n; ++i) {
        char color;
        int left, len;
        cin >> color;
        cin >> left >> len;
        int right = left + len;
        L = min(L, left);
        R = max(R, right);
        q[i] = Query(left, right, color == 'B');
    }

    if (L < 0) {
        for (int i = 0; i < n; ++i) {
            q[i].left -= L;
            q[i].right -= L;
            R = max(R, q[i].right);
        }
    }

    SegmentTree tree(R);
    for (int i = 0; i < n; ++i) {
        tree.update(q[i].left, q[i].right, q[i].color);
        cout << tree.count() << "\n";
    }

    delete[] q;
    return 0;
}