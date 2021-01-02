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

template <typename T>
class Forest {
    struct Node {
        T value;
        T priority;

        int cnt;
        bool cycle;

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        Node(T x) : value(x), priority(rng()), cnt(1), cycle(false) {}
    };
    vector<Node*> trees;

    using Pair = pair<Node*, Node*>;

    int count(Node* node) {
        return node ? node->cnt : 0;
    }

    void update(Node* &node) {
        if (!node) return;
        node->cnt = 1 + count(node->left) + count(node->right);
    }

    void hang_to(Node* &child, Node* parent) {
        if (!child) return;
        child->parent = parent;
    }

    Pair split(Node* node, int k) {
        if (!node) {
            return {nullptr, nullptr};
        }
        int key = count(node->left);
        if (key >= k) {
            auto [first, second] = split(node->left, k);
            node->left = second;
            hang_to(second, node);
            update(node);
            return {first, node};
        }
        auto [first, second] = split(node->right, k - key - 1);
        node->right = first;
        hang_to(first, node);
        update(node);
        return {node, second};
    }

    Node* merge(Node* first, Node* second) {
        if (!first) {
            return second;
        } else if (!second) {
            return first;
        } else if (first->priority > second->priority) {
            auto tmp = merge(first->right, second);
            first->right = tmp;
            hang_to(tmp, first);
            update(first);
            return first;
        }
        auto tmp = merge(first, second->left);
        second->left = tmp;
        hang_to(tmp, second);
        update(second);
        return second;
    }

    void reverse(Node* &node) {
        if (!node) return;
        swap(node->left, node->right);
        reverse(node->left);
        reverse(node->right);
    }

    Node* get_root(Node* node) {
        while (node && node->parent) {
            node = node->parent;
        }
        return node;
    }

    Node* min_node(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* max_node(Node* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    Pair get_ends(Node* node) {
        return {min_node(node), max_node(node)};
    }

public:
    Forest(T n) {
        for (T v = 0; v <= n; ++v) {
            trees.push_back(new Node(v));
        }
    }

    void merge(T i, T j) {
        auto first = trees[i], second = trees[j];
        auto first_root = get_root(first);
        auto second_root = get_root(second);

        if (first_root == second_root) {
            auto [left, right] = get_ends(first_root);
            if ((left == first && right == second) ||
                (left == second && right == first)) {
                first_root->cycle = true;
            }
            return;
        }

        auto [first_left, first_right] = get_ends(first_root);
        auto [second_left, second_right] = get_ends(second_root);

        if (first_right == first && second_left == second) {
            merge(first_root, second_root);
        } else if (first_left == first && second_right == second) {
            merge(second_root, first_root);
        } else if (first_left == first && second_left == second) {
            reverse(first_root);
            merge(first_root, second_root);
        } else {
            reverse(second_root);
            merge(first_root, second_root);
        }
    }

    int get_index(Node* node) {
        int ind = count(node->left);
        while (node->parent) {
            if (node == node->parent->right) {
                ind += count(node->parent->left) + 1;
            }
            node = node->parent;
        }
        return ind;
    }

    void split(T i, T j) {
        auto first = trees[i], second = trees[j];
        auto first_root = get_root(first);
        int first_ind = get_index(first);
        int second_ind = get_index(second);

        if (!first_root->cycle) {
            if (first_ind + 1 == second_ind) {
                auto [left, right] = split(first_root, second_ind);
                hang_to(left, nullptr);
                hang_to(right, nullptr);
            } else {
                auto [left, right] = split(first_root, first_ind);
                hang_to(left, nullptr);
                hang_to(right, nullptr);
            }
            return;
        }

        auto [left, right] = get_ends(first_root);
        first_root->cycle = false;

        if ((left == first && right == second) ||
            (left == second && right == first)) return;

        if (first_ind + 1 == second_ind) {
            auto [left, right] = split(first_root, second_ind);
            hang_to(left, nullptr);
            hang_to(right, nullptr);

            Node* ff = get_root(trees[i]);
            Node* ss = get_root(trees[j]);
            reverse(ff), reverse(ss);
            merge(ff, ss);

        } else {
            auto [left, right] = split(first_root, first_ind);
            hang_to(left, nullptr);
            hang_to(right, nullptr);

            Node* ff = get_root(trees[i]);
            Node* ss = get_root(trees[j]);
            reverse(ff), reverse(ss);
            merge(ss, ff);
        }
        get_root(trees[i])->cycle = false;
        get_root(trees[j])->cycle = false;
    }

    int distance(T i, T j) {
        if (i == j)  return 0;
        auto first = trees[i], second = trees[j];
        auto first_root = get_root(first);
        auto second_root = get_root(second);

        if (first_root != second_root) return -1;
        int first_ind = get_index(first);
        int second_ind = get_index(second);

        if (!first_root->cycle) {
            return abs(first_ind - second_ind) - 1;
        }

        if (first_ind > second_ind) {
            swap(first_ind, second_ind);
        }

        int mx = get_index(max_node(first_root));
        return min(mx - second_ind + first_ind, second_ind - first_ind - 1);
    }
};

void solve() {
    int n, m, q;
    cin >> n >> m >> q;

    Forest<int> forest(n);
    for (int i, j; m-- && cin >> i >> j;) {
        forest.merge(i, j);
    }

    for (char cmd; cin >> cmd && q--;) {
        int i, j;
        cin >> i >> j;
        if (cmd == '+') {
            forest.merge(i, j);
        } else if (cmd == '-') {
            forest.split(i, j);
        } else {
            cout << forest.distance(i, j) << endl;
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