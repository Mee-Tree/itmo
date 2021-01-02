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

const int INF = 2e9 + 1337;
mt19937 rng((uint64_t) new char);

template<typename T>
class Treap {
    struct Node {
        T key;
        T priority;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(T x, T y): key(x), priority(y) {}
    }* root;

    auto min(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    auto max(Node* node) {
        while (node && node->right) {
            node = node->right;
        }
        return node;
    }

    void split(T x, Node* node, Node* &first, Node* &second) {
        if (!node) {
            first = nullptr;
            second = nullptr;
        } else if (x > node->key) {
            split(x, node->right, node->right, second);
            first = node;
        } else {
            split(x, node->left, first, node->left);
            second = node;
        }
    }

    void merge(Node* &node, Node* first, Node* second) {
        if (!first) {
            node = second;
        } else if (!second) {
            node = first;
        } else if (first->priority > second->priority) {
            merge(first->right, first->right, second);
            node = first;
        } else  {
            merge(second->left, first, second->left);
            node = second;
        }
    }

    void insert(T x, T y, Node* &node) {
        if (!node) {
            node = new Node(x, y);
        } else if (node->priority < y) {
            auto tmp = new Node(x, y);
            split(x, node, tmp->left, tmp->right);
            node = tmp;
        } else {
            insert(x, y, node->key < x ? node->right : node->left);
        }
   }

    void remove(T x, Node* &node) {
        if (node->key == x) {
            merge(node, node->left, node->right);
        } else {
            remove(x, node->key < x ? node->right : node->left);
        }
    }

    void next(T x, Node* node, Node* &nxt) {
        if (!node)  return;

        if (node->key > x) {
            nxt = node;
            next(x, node->left, nxt);
        } else if (node->key < x) {
            next(x, node->right, nxt);
        } else if (node->right) {
            nxt = min(node->right);
        }
    }

    void prev(T x, Node* node, Node* &prv) {
        if (!node)  return;

        if (node->key < x) {
            prv = node;
            prev(x, node->right, prv);
        } else if (node->key > x) {
            prev(x, node->left, prv);
        } else if (node->left) {
            prv = max(node->left);
        }
    }
public:
    Treap() {
        root = nullptr;
    }

    void insert(T x) {
        if (exists(x)) return;
        insert(x,  rng() % INF, root);
    }

    void remove(T x) {
        if (!exists(x)) return;
        remove(x, root);
    }

    bool exists(T x) {
        auto node = root;
        while (node && node->key != x) {
            if (node->key < x) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return node != nullptr;
    }

    T next(T x) {
        Node* nxt = nullptr;
        next(x, root, nxt);
        return nxt ? nxt->key : INF;
    }

    T prev(T x) {
        Node* prv = nullptr;
        prev(x, root, prv);
        return prv ? prv->key : INF;
    }

    ~Treap() {
        delete root;
    }
};

void solve() {
    Treap<int> bst;
    for (string cmd; cin >> cmd;) {
        int x;
        cin >> x;
        if (cmd == "insert") {
            bst.insert(x);
        } else if (cmd == "delete") {
            bst.remove(x);
        } else if (cmd == "next") {
            int res = bst.next(x);
            if (res == INF) {
                cout << "none\n";
                continue;
            }
            cout << res << "\n";
        } else if (cmd == "prev") {
            int res = bst.prev(x);
            if (res == INF) {
                cout << "none\n";
                continue;
            }
            cout << res << "\n";
        } else {
            cout << (bst.exists(x) ? "true" : "false") << "\n";
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


