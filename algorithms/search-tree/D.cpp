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
        T sum = 0;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y): key(x), priority(y) {}
    }* root;

    Node* min(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Node* max(Node* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    void update(Node* &node) {
        if (!node) return;
        node->sum = node->key;
        if (node->left) {
            node->sum += node->left->sum;
        }
        if (node->right) {
            node->sum += node->right->sum;
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

    T sum(T l, T r, Node* node) {
        if (!node)  return 0;
        T mn = min(node)->key;
        T mx = max(node)->key;
        if (r < mn || l > mx) {
            return 0;
        }
        if (l <= mn && mx <= r) {
            return node->sum;
        }
        T tmp = (l <= node->key && node->key <= r) * node->key;
        return tmp + sum(l, r, node->left) + sum(l, r, node->right);
    }
public:
    Treap() {
        root = nullptr;
    }

    void insert(T x) {
        if (exists(x)) return;
        insert(x, rng(), root);
    }

    T sum(T l, T r) {
        return sum(l, r, root);
    }

    bool exists(T x) {
        auto node = root;
        while (node) {
            if (node->key < x) {
                node = node->right;
            } else if (node->key > x){
                node = node->left;
            } else break;
        }
        return node != nullptr;
    }

    ~Treap() {
        delete root;
    }
};

void solve() {
    int n;
    cin >> n;

    Treap<long long> treap;
    long long prev = 0;
    for (char cmd; n && cin >> cmd; --n) {
        if (cmd == '+') {
            int x;
            cin >> x;
            treap.insert((prev + x) % MOD);
            prev = 0;
        } else {
            int l, r;
            cin >> l >> r;
            prev = treap.sum(l, r);
            cout << prev << endl;
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

