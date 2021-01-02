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

const int INF = 1e9 + 228;
const int MOD = 1e9;

class SegmentTree {
    vector<T> tree;
    int sz;

    const T E = 0;
    T op(T a, T b) {
        return a + b;
    }

    T sum(int x, int lx, int rx, int l, int r) {
        if (rx <= l || lx >= r) {
            return E;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }

        int mx = (lx + rx) / 2;
        T left  = sum(2 * x + 1, lx, mx, l, r);
        T right = sum(2 * x + 2, mx, rx, l, r);
        return op(left, right);
    }

    void update(int x, int lx, int rx, int ind, T val) {
        if (rx - lx == 1) {
            tree[x] = val;
            return;
        }

        int mx = (lx + rx) / 2;
        if (ind < mx) {
            update(2 * x + 1, lx, mx, ind, val);
        } else {
            update(2 * x + 2, mx, rx, ind, val);
        }
        tree[x] = op(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(vector<T> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = a[lx];
            return;
        }

        int mx = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mx);
        build(a, 2 * x + 2, mx, rx);
        tree[x] = op(tree[2 * x + 1], tree[2 * x + 2]);
    }
public:
    explicit SegmentTree(vector<T> &a) {
        sz = (int)a.size();
        tree.resize(4 * sz);
        build(a, 0, 0, sz);
    }

    T sum(int l, int r) {
        return sum(0, 0, sz, l, r);
    }

    void update(int ind, T val) {
        update(0, 0, sz, ind, val);
    }
};

signed main() {
    int n;
    cin >> n;
    vector<T> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    SegmentTree tree(a);
    string cmd;
    while (cin >> cmd) {
        T x, y;
        cin >> x >> y;
        --x;
        if (cmd == "set") {
            tree.update(x, y);
        } else {
            cout << tree.sum(x, y) << "\n";
        }
    }

    return 0;
}
