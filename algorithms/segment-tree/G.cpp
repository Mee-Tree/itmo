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

typedef pair<int, int> pii;

const int INF = 1e9 + 228;
const int MOD = 1e9;

struct Point;

struct Node {
    int val;
    int add;
    int y;

    Node(): val(0), add(0), y(0) {}
};


class SegmentTree {
    Node* tree;
    int n;

    const Node E = Node();

    void propagate(int x, int lx, int rx) {
        if (rx - lx == 1 || tree[x].add == E.add) return;

        int mx = (lx + rx) / 2;
        for (int i = 1; i <= 2; ++i) {
            tree[2 * x + i].add += tree[x].add;
            tree[2 * x + i].val += tree[x].add;
        }
        tree[x].add = E.add;
    }

    Node combine(Node a, Node b) {
        Node c = b;
        if (a.val > b.val) {
            c.val = a.val;
            c.y = a.y;
        }
        c.add = 0;
        return c;
    }

    Node getMax(int x, int lx, int rx, int l, int r) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return E;
        }
        if (l <= lx && rx <= r) {
            return tree[x];
        }
        int mx = (lx + rx) / 2;
        Node left = getMax(2 * x + 1, lx, mx, l, r);
        Node right = getMax(2 * x + 2, mx, rx, l, r);
        return combine(left, right);
    }

    void update(int x, int lx, int rx, int l, int r, int val) {
        propagate(x, lx, rx);
        if (rx <= l || lx >= r) {
            return;
        }
        if (l <= lx && rx <= r) {
            tree[x].add += val;
            tree[x].val += val;
            return;
        }
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, val);
        update(2 * x + 2, mx, rx, l, r, val);
        tree[x] = combine(tree[2 * x + 1], tree[2 * x + 2]);
    }

    void build(int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x].y = lx;
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

    Node getMax() {
        return getMax(0, 0, n, 0, n);
    }

    void update(int l, int r, int val) {
        update(0, 0, n, l, r, val);
    }

    ~SegmentTree() {
        delete[] tree;
    }
};

struct Point {
    int x, y;

    Point(): x(0), y(0) {}

    friend istream& operator>> (istream& in, Point& a) {
        in >> a.x >> a.y;
        return in;
    }

    friend ostream& operator<< (ostream& out, const Point& a) {
        out << a.x << " " << a.y;
        return out;
    }
};

struct Query {
    int x, type;
    int left, right;

    Query(int x, int type, int left, int right): x(x), type(type), left(left), right(right) {}

    friend bool operator< (const Query& a, const Query& b) {
        return  (a.x < b.x) ||
                (a.x == b.x && a.type > b.type);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;

    int deltaX = 0, deltaY = 0;
    vector<Query> windows;
    for (int i = 0; i < n; ++i) {
        Point a, b;
        cin >> a >> b;

        deltaX = min({deltaX, a.x, b.x});
        deltaY = min({deltaY, a.y, b.y});

        int left = min(a.y, b.y);
        int right = max(a.y, b.y) + 1;

        windows.emplace_back(a.x, 1, left, right);
        windows.emplace_back(b.x, -1, left, right);
    }

    int size = 0;
    for_each(windows.begin(), windows.end(), [&](Query& a) {
        a.x -= deltaX;
        a.left -= deltaY;
        a.right -= deltaY;
        size = max(size, a.right);
    });

    sort(windows.begin(), windows.end());

    int mx = 0;
    Point ans;

    SegmentTree tree(++size);
    for (Query& query : windows) {
        tree.update(query.left, query.right, query.type);

        Node cur = tree.getMax();
        if (cur.val > mx) {
            mx = cur.val;
            ans.x = query.x + deltaX;
            ans.y = cur.y + deltaY;
        }
    }

    cout << mx << "\n" << ans;

    return 0;
}