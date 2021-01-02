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

#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

const int INF = 2e9 + 1337;

class Automaton {
    static const int ALPHABET_SIZE = 26;
    const int ROOT = 0;

public:
    Automaton() { nodes.emplace_back(); }

    void add(const string& s) {
        int u = ROOT;
        for (char ch : s) {
            int c = ch - 'a';
            if (nodes[u].next[c] == -1) {
                nodes[u].next[c] = nodes.size();
                nodes.emplace_back(c, u);
            }
            u = nodes[u].next[c];
        }

        nodes[u].inds.emplace_back(strs.size());
        strs.emplace_back(s);
    }

    vector<pair<int, int>> process(const string& str) {
        set_suffix_links();
        int u = ROOT;
        for (int i = 0; i < str.size(); ++i) {
            u = next(u, str[i] - 'a');
            if (nodes[u].left == INF) {
                nodes[u].left = i;
            }
            nodes[u].right = i;
        }

        for (int i = 0; i < nodes.size(); ++i) {
            for (int j = i; j != ROOT; j = nodes[j].suf_link) {
                int suf = nodes[j].suf_link;
                nodes[suf].left = min(nodes[suf].left, nodes[j].left);
                nodes[suf].right = max(nodes[suf].right, nodes[j].right);
            }
        }

        vector<pair<int, int>> result(strs.size());
        for (auto& node : nodes) {
            for (int ind : node.inds) {
                result[ind] = node.left == INF ? make_pair(-1, -1) :
                    make_pair((int) (node.left - strs[ind].size() + 1)
                            , (int) (node.right - strs[ind].size() + 1));
            }
        }
        return result;
    }

private:
    int next(int u, int ch) {
        while (u != -1 && nodes[u].next[ch] == -1) {
            u = nodes[u].suf_link;
        }
        return u == -1 ? ROOT : nodes[u].next[ch];
    }

    void set_suffix_links() {
        queue<int> q;
        q.push(ROOT);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            set_suf_link(u);
            for (int next : nodes[u].next) {
                if (next != -1) {
                    q.push(next);
                }
            }
        }
    }

    void set_suf_link(int u) {
        if (u == ROOT) { return; }

        int ch = nodes[u].ch;
        int p = nodes[nodes[u].parent].suf_link;
        while (p != -1 && nodes[p].next[ch] == -1) {
            p = nodes[p].suf_link;
        }

        attach(u, p == -1 ? ROOT : nodes[p].next[ch]);
    }

    void attach(int u, int v) {
        nodes[u].suf_link = v;
        nodes[v].rsufs.emplace_back(u);
    }

    struct Node {
        vector<int> next;
        int ch, parent;

        vector<int> rsufs, inds;
        int left = INF, right = -1;
        int suf_link = - 1;

        explicit Node(int ch = 0, int parent = -1)
                : next(ALPHABET_SIZE, -1)
                , ch(ch), parent(parent) {}
    };

    vector<string> strs;
    vector<Node> nodes;
};

void solve() {
    int n;
    cin >> n;

    Automaton aut;
    for (string s; n-- && cin >> s; ) {
        aut.add(s);
    }

    string text;
    cin >> text;

    for (auto [l, r] : aut.process(text)) {
        cout << l << " " << r << endl;
    }
}

signed main() {
#ifdef LOCAL
    const string FILENAME = "local";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}