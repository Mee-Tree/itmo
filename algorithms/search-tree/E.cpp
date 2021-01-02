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
class Treap {
    struct Node {
        T key;
        T priority;
        int cnt = 1;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y): key(x), priority(y) {}
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

    void split(T x, Node* node, Node* &first, Node* &second) {
        if (!node) {
            first = nullptr;
            second = nullptr;
        } else if (node->key < x) {
            split(x, node->right, node->right, second);
            first = node;
        } else {
            split(x, node->left, first, node->left);
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

    void insert(T x, T y, Node* &node) {
        if (!node) {
            node = new Node(x, y);
        } else if (node->priority < y) {
            auto tmp = new Node(x, y);
            split(x, node, tmp->left, tmp->right);
            node = tmp;
        } else if (node->key < x) {
            insert(x, y, node->right);
        } else {
            insert(x, y, node->left);
        }
        update(node);
    }

    void remove(T x, Node* &node) {
        if (node->key < x) {
            remove(x, node->right);
        } else if (node->key > x) {
            remove(x, node->left);
        } else {
            merge(node, node->left, node->right);
        }
        update(node);
    }

    int cnt(Node* node) {
        return node ? node->cnt : 0;
    }

    T max(int k, Node* node) {
        if (k - 1 > cnt(node->right)) {
            return max(k - 1 - cnt(node->right), node->left);
        } else if (k - 1 < cnt(node->right)){
            return max(k, node->right);
        } else {
            return node->key;
        }
    }
public:
    Treap() {
        root = nullptr;
    }

    void insert(T x) {
        insert(x, rng(), root);
    }

    void remove(T x) {
        remove(x, root);
    }

    T max(int k) {
        return max(k, root);
    }

    ~Treap() {
        delete root;
    }
};

void solve() {
    int n;
    cin >> n;

    Treap<int> treap;
    for (int cmd, k; n && cin >> cmd >> k; --n) {
        if (cmd == 1) {
            treap.insert(k);
        } else if (cmd == -1) {
            treap.remove(k);
        } else {
            cout << treap.max(k) << endl;
        }
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

