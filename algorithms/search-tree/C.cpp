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

        int cnt;
        bool zero;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y)
            : value(x), priority(y),
            cnt(1), zero(x == 0) {}
    }* root;

    int count(Node* node) {
        return node ? node->cnt : 0;
    }

    bool has_zero(Node* node) {
        return node ? node->zero : false;
    }

    void update(Node* &node) {
        if (!node) return;
        node->cnt = 1 + count(node->left) + count(node->right);
        node->zero = (node->value == 0) || has_zero(node->left) || has_zero(node->right);
    }

    void split(int pos, Node* node, Node* &first, Node* &second) {
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

    void remove_zero(Node* &node) {
        if (!has_zero(node)) return;
        if (has_zero(node->left)) {
            remove_zero(node->left);
        } else if (node->value == 0) {
            merge(node, node->left, node->right);
        } else {
            remove_zero(node->right);
        }
        update(node);
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
            v[i] = {0, rng()};
        }
        build(v);
    }

    void insert(int pos, T x) {
        Node* left = nullptr;
        Node* right = nullptr;
        split(pos - 1, root, left, right);
        remove_zero(right);
        merge(right, new Node(x, rng()), right);
        merge(root, left, right);
    }

    void traverse() {
        vector<T> v;
        traverse(v, root);
        while (!v.empty() && v.back() == 0) {
            v.pop_back();
        }
        cout << v.size() << endl;
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
    ImplicitTreap<int> tree(n + m);
    for (int num = 1, l; n && cin >> l; --n, ++num) {
        tree.insert(l, num);
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
