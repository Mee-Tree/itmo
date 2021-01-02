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

const int MOD = 1e9;
mt19937 rng((uint64_t) new char);

template<typename T>
class ImplicitTreap {
    struct Node {
        T value;
        T priority;

        int cnt = 1;
        bool reversed = false;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y): value(x), priority(y) {}
    }* root;

    void propagate(Node* &node) {
        if (!node || !node->reversed) return;
        swap(node->left, node->right);
        if (node->left) {
            node->left->reversed ^= true;
        }
        if (node->right) {
            node->right->reversed ^= true;
        }
        node->reversed = false;
    }

    void update(Node* &node) {
        if (!node) return;
        node->cnt = 1;
        if (node->left) {
            node->cnt += node->left->cnt;
        }
        if (node->right) {
            node->cnt += node->right->cnt;
        }
    }

    int count(Node* node) {
        return node ? node->cnt : 0;
    }

    void split(int pos, Node* node, Node* &first, Node* &second) {
        propagate(node);
        if (!node) {
            first = nullptr;
            second = nullptr;
            return;
        }
        int key = count(node->left);
        if (key < pos) {
            split(pos - key - 1, node->right, node->right, second);
            first = node;
        } else {
            split(pos, node->left, first, node->left);
            second = node;
        }
        update(first);
        update(second);
    }

    void merge(Node* &node, Node* first, Node* second) {
        propagate(first);
        propagate(second);
        if (!first) {
            node = second;
        } else if (!second) {
            node = first;
        } else if (first->priority > second->priority) {
            merge(first->right, first->right, second);
            node = first;
        } else {
            merge(second->left, first, second->left);
            node = second;
        }
        update(node);
    }

    void insert(int pos, T x, T y, Node* &node) {
        if (!node) {
            node = new Node(x, y);
        } else if (node->priority < y) {
            auto tmp = new Node(x, y);
            split(pos, node, tmp->left, tmp->right);
            node = tmp;
        } else {
            int key = count(node->left);
            if (key < pos) {
                insert(pos - key - 1, x, y, node->right);
            } else {
                insert(pos, x, y, node->left);
            }
        }
        update(node);
    }

    void reverse(int l, int r, Node* &node) {
        Node* left = nullptr;
        Node* mid = nullptr;
        Node* right = nullptr;
        split(l, node, left, mid);
        split(r - l + 1, mid, mid, right);
        mid->reversed ^= true;
        merge(node, left, mid);
        merge(node, node, right);
    }

    void build(vector<pair<T, T>> &v) {
        for (int i = 0; i < v.size(); ++i) {
            T x = v[i].first;
            T y = v[i].second;
            insert(i, x, y, root);
        }
    }

    void traverse(vector<T> &v, Node* node) {
        if (!node) {
            return;
        }
        propagate(node);
        traverse(v, node->left);
        v.push_back(node->value);
        traverse(v, node->right);
    }
public:
    ImplicitTreap() {
        root = nullptr;
    }

    ImplicitTreap(T n) {
        root = nullptr;
        vector<pair<T, T>> v(n);
        for (size_t i = 0; i < n; ++i) {
            v[i] = {i + 1, rng()};
        }
        build(v);
    }

    void reverse(T l, T r) {
        reverse(l - 1, r - 1, root);
    }

    void traverse() {
        vector<T> v;
        traverse(v, root);
        for (auto num : v) {
            cout << num << " ";
        }
    }

    ~ImplicitTreap() {
        delete root;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    ImplicitTreap<int> tree(n);
    for (int l, r; m && cin >> l >> r; --m) {
        tree.reverse(l, r);
    }
    tree.traverse();
}

int main() {
#ifdef LOCAL
    const string FILENAME = "bst";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}

