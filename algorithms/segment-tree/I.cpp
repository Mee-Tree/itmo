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

typedef long long ll;
typedef pair<int, int> pii;

const ll INF = 2e18 + 228;

struct Node {
    ll max = 0;
    ll sum = 0;
    ll inc = -INF;

    int lx = 0;
    int rx = 0;

    Node* left = nullptr;
    Node* right = nullptr;

    Node(int l, int r) : lx(l), rx(r) {}

    void ensureChildren() {
        int mx = (lx + rx) / 2;
        if (left == nullptr) {
            left = new Node(lx, mx);
        }
        if (right == nullptr) {
            right = new Node(mx, rx);
        }
    }
};

class SegmentTree {
    Node* root;

    void propagate(Node* x) {
        x->ensureChildren();

        if (x->inc == -INF) return;

        for (auto& child : {x->left, x->right}) {
            child->inc = x->inc;
            child->sum = (child->rx - child->lx) * x->inc;
            child->max = (child->rx - child->lx) * x->inc;
        }
        x->inc = -INF;
    }

    int count(Node* x, ll h) {
        if (x->rx - x->lx == 1) {
            if (x->max > h) {
                return x->lx;
            }
            return x->rx;
        }
        propagate(x);
        if (x->left->max > h) {
            return count(x->left, h);
        } else {
            h -= x->left->sum;
            return count(x->right, h);
        }
    }

    void update(Node* x, int l, int r, ll val) {
        if (x->rx <= l || x->lx >= r) {
            return;
        }
        if (l <= x->lx && x->rx <= r) {
            x->max = (x->rx - x->lx) * val;
            x->sum = (x->rx - x->lx) * val;
            x->inc = val;
            return;
        }
        propagate(x);
        update(x->left, l, r, val);
        update(x->right, l, r, val);
        x->sum = x->left->sum + x->right->sum;
        x->max = max(x->left->max, x->right->max + x->left->sum);
    }
public:
    explicit SegmentTree(int n) {
        root = new Node(0, n);
    }

    int count(ll h) {
        return count(root, h);
    }

    void update(int l, int r, ll val) {
        update(root, l, r, val);
    }

    ~SegmentTree() {
        delete root;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    char cmd;
    SegmentTree tree(n);
    while (cin >> cmd && cmd != 'E') {
        switch (cmd) {
            case 'I':
                int a, b;
                ll d;
                cin >> a >> b >> d;
                tree.update(--a, b, d);
                break;
            case 'Q':
                ll h;
                cin >> h;
                cout << tree.count(h) << "\n";
                break;
        }
    }
    return 0;
}