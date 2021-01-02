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

template<typename T>
class BinarySearchTree {
    struct Node {
        T val;

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        explicit Node(T val): val(val) {}
    }* root;

    auto find(T x, Node* node) {
        if (!node || node->val == x) {
            return node;
        }
        if (node->val < x) {
            return find(x, node->right);
        }
        return find(x, node->left);
    }

    auto min(Node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    void insert(T x, Node* &node) {
        if (!node) {
            node = new Node(x);
            return;
        }
        if (x < node->val) {
            insert(x, node->left);
            node->left->parent = node;
        } else if (x > node->val) {
            insert(x, node->right);
            node->right->parent = node;
        }
    }

    void replace(Node* &node, Node* &new_node){
        if (!node) return;
        if (!node->parent) {
            node = new_node;
            if (node) {
                node->parent = nullptr;
            }
            return;
        }
        if (node == node->parent->right) {
            node->parent->right = new_node;
        } else {
            node->parent->left = new_node;
        }
        if (new_node) {
            new_node->parent = node->parent;
        }

    };

    void erase(T x, Node* &node) {
        if (!node) return;

        if (x < node->val) {
            erase(x, node->left);
        } else if (x > node->val) {
            erase(x, node->right);
        } else {
            if (!node->right) {
                replace(node, node->left);
                return;
            }
            auto new_node = min(node->right);
            node->val = new_node->val;
            replace(new_node, new_node->right);
        }
    }

    void next(T x, Node* node, Node* &nxt) {
        if (!node) return;
        next(x, node->left, nxt);
        if (node->val > x && !nxt) {
            nxt = node;
            return;
        }
        next(x, node->right, nxt);
    }

    void prev(T x, Node* node, Node* &prv) {
        if (!node)  return;

        prev(x, node->right, prv);
        if (node->val < x && !prv) {
            prv = node;
            return;
        }
        prev(x, node->left, prv);
    }
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(T x) {
        insert(x, root);
    }

    void erase(T x) {
        erase(x, root);
    }

    bool exists(T x) {
        return find(x, root) != nullptr;
    }

    T next(T x) {
        Node* nxt = nullptr;
        next(x, root, nxt);
        return nxt ? nxt->val : INF;
    }

    T prev(T x) {
        Node* prv = nullptr;
        prev(x, root, prv);
        return prv ? prv->val : INF;
    }

    ~BinarySearchTree() {
        delete root;
    }
 };

void solve() {
    BinarySearchTree<int> bst;
    for (string cmd; cin >> cmd;) {
        int x;
        cin >> x;
        if (cmd == "insert") {
            bst.insert(x);
        } else if (cmd == "delete") {
            bst.erase(x);
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


