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
        T priority;
        T value;
        int cnt = 1;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y): value(x), priority(y) {}
    }* root;

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

    void split(T pos, Node* node, Node* &first, Node* &second) {
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

    void remove(T pos, Node* &node) {
        int key = count(node->left);
        if (key == pos) {
            merge(node, node->left, node->right);
        } else if (key < pos) {
            remove(pos - key - 1, node->right);
        } else {
            remove(pos, node->left);
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

    ImplicitTreap(vector<T> &v) {
        root = nullptr;
        vector<pair<T, T>> vv(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            vv[i] = {v[i], rng()};
        }
        build(vv);
    }

    void insert(int pos, T x) {
        insert(pos, x, rng(), root);
    }

    void remove(int pos) {
        remove(pos, root);
    }

    void traverse(vector<T> &v) {
        traverse(v, root);
    }

    ~ImplicitTreap() {
        delete root;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> v(n);
    for (size_t i = 0; i < n; ++i) {
        cin >> v[i];
    }

    ImplicitTreap<int> tree(v);
    for (string cmd; m && cin >> cmd; --m) {
        if (cmd == "add") {
            int i, x;
            cin >> i >> x;
            tree.insert(i, x);
        } else {
            int i;
            cin >> i;
            tree.remove(i - 1);
        }
    }

    vector<int> res;
    tree.traverse(res);
    cout << res.size() << endl;
    for (auto num : res) {
        cout << num << " ";
    }
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

