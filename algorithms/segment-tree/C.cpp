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
using T = long long;

const long long INF = 2e18;
const int MOD = 1e9;

struct Node {
    T set;
    T add;

    Node(): set(INF), add(0){}

    bool equals(const Node a) {
        return set == a.set && add == a.add;
    }
};

class SegmentTree {
    T* tree;
    Node* rangeOp;
    int n;

    const T E = INF;
    const Node _E = Node();

    void propagate (int x, int lx, int rx) {
        if (rx - lx == 1 || rangeOp[x].equals(_E)) return;
        for (int i = 1; i <= 2; ++i) {
            if (rangeOp[x].set == _E.set) {
                rangeOp[2 * x + i].add += rangeOp[x].add;
            } else {
                rangeOp[2 * x + i] = rangeOp[x];
                tree[2 * x + i] = rangeOp[x].set;
            }
            tree[2 * x + i] += rangeOp[x].add;
        }
        rangeOp[x] = _E;
    }

    T rmq(int x, int lx, int rx, int l, int r) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return E;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        T left  = rmq(2 * x + 1, lx, mx, l, r);
        T right = rmq(2 * x + 2, mx, rx, l, r);
        return min(left, right);
    }

    void update(int x, int lx, int rx, int l, int r, T addVal, T setVal) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return;
        }
        if (lx >= l && rx <= r) {
            if (setVal != _E.set) {
                rangeOp[x].set = setVal;
                tree[x] = setVal;
            }
            rangeOp[x].add += addVal;
            tree[x] += addVal;
            return;
        }
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, addVal, setVal);
        update(2 * x + 2, mx, rx, l, r, addVal, setVal);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = a[lx];
            return;
        }
        int mx = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mx);
        build(a, 2 * x + 2, mx, rx);
        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
public:
    explicit SegmentTree(vector<T> &a) {
        n = (int)a.size();
        tree = new T[4 * n];
        rangeOp = new Node[4 * n];
        build(a, 0, 0, n);
    }

    T rmq(int l, int r) {
        return rmq(0, 0, n, l, r);
    }

    void update(int l, int r, T addVal, T setVal) {
        update(0, 0, n, l, r, addVal, setVal);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    vector<T> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree tree(a);
    string cmd;
    while (cin >> cmd) {
        int l, r, val;
        cin >> l >> r;
        --l;
        if (cmd == "min") {
            cout << tree.rmq(l, r) << "\n";
            continue;
        }
        cin >> val;
        if (cmd == "set") {
            tree.update(l, r, 0, val);
        } else {
            tree.update(l, r, val, INF);
        }
    }
    return 0;
}