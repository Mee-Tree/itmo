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

class FenwickTree {
    T* tree;
    int n;
public:
    explicit FenwickTree(int size) {
        n = size;
        tree = new T[n * n * n];
        fill_n(tree, n * n * n, 0);
    }

    void update(int x, int y, int z, int val) {
        for (x; x < n; x = x | (x + 1)) {
            for (int i(y); i < n; i = i | (i + 1)) {
                for (int j(z); j < n; j = j | (j + 1)) {
                    tree[x * n * n + i * n + j] += val;
                }
            }
        }
    }


    T rsq(int x, int y, int z) {
        T res = 0;
        for (x; x >= 0; x = (x & (x + 1)) - 1) {
            for (int i(y); i >= 0; i = (i & (i + 1)) - 1) {
                for (int j(z); j >= 0; j = (j & (j + 1)) - 1) {
                    res += tree[x * n * n + i * n + j];
                }
            }
        }

        return res;
    }

    ~FenwickTree() {
        delete[] tree;
    }
};

struct Point {
    vector<int> c;

    explicit Point(int dim) {
        c.resize(dim);
    }

    int& operator[](unsigned ind) {
        return c[ind];
    }

    unsigned getDim() {
        return c.size();
    }
};

istream& operator>> (istream &in, Point &a) {
    for (int i = 0; i < a.getDim(); ++i) {
        in >> a[i];
    }
    return in;
}

#define STANDARD_IN_OUT

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    int dim = 3;
    FenwickTree tree(n);
    for (int cmd; cin >> cmd && cmd != 3;) {
        Point a(dim), b(dim);
        int val;
        cin >> a;

        if (cmd == 1) {
            cin >> val;
            tree.update(a[0], a[1], a[2], val);
            continue;
        }
        cin >> b;

        T res = 0;
        for (int i = 0; i < (1 << dim); ++i) {
            int cnt = 0;
            Point c(dim);
            for (int j = 0; j < dim; ++j) {
                if (i & (1 << j)) {
                    c[j] = b[j];
                    ++cnt;
                    continue;
                }
                c[j] = a[j] - 1;
            }
            res += (cnt % 2 ? 1 : -1) * tree.rsq(c[0], c[1], c[2]);
        }

        cout << res << "\n";
    }

    return 0;
}