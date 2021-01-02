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

struct matrix {
    int m[2][2];

    matrix() = default;

    matrix(int a00, int a01, int a10, int a11) {
        m[0][0] = a00;
        m[0][1] = a01;
        m[1][0] = a10;
        m[1][1] = a11;
    }
};

using T = matrix;

const int INF = 1e9 + 228;

int MOD = 1e9;

istream& operator>> (istream &in, T &a) {
    in >> a.m[0][0] >> a.m[0][1];
    in >> a.m[1][0] >> a.m[1][1];
    a.m[0][0] %= MOD, a.m[0][1] %= MOD;
    a.m[1][0] %= MOD, a.m[1][1] %= MOD;
    return in;
}


ostream& operator<< (ostream &out, const T &a) {
    out << a.m[0][0] << " " << a.m[0][1] << "\n";
    out << a.m[1][0] << " " << a.m[1][1] << "\n\n";
    return out;
}

class SegmentTree {
    T* tree;
    int n;

    const T E = T(
            1, 0,
            0, 1
    );
    T op(T a, T b) {
        return {
                (a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0]) % MOD,
                (a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1]) % MOD,
                (a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0]) % MOD,
                (a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1]) % MOD
        };
    }

    T mul(int x, int lx, int rx, int l, int r) {
        if (rx <= l || lx >= r) {
            return E;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        T left  = mul(2 * x + 1, lx, mx, l, r);
        T right = mul(2 * x + 2, mx, rx, l, r);
        return op(left, right);
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
        n = (int)a.size();
        tree = new T[4 * n];
        build(a, 0, 0, n);
    }

    T mul(int l, int r) {
        return mul(0, 0, n, l, r);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

signed main() {
    string FILENAME = "crypto";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> MOD >> n >> m;

    vector<T> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree tree(a);
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        cout << tree.mul(--l, r);
    }
    return 0;
}