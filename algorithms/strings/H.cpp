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
        indices.emplace_back(u);
    }

    vector<int> process(const string& str) {
        set_suffix_links();
        int u = ROOT;
        nodes[u].terminal = 1;
        for (char ch : str) {
            u = next(u, ch - 'a');
            ++nodes[u].terminal;
        }
        count_terminals(ROOT);

        vector<int> result;
        for (int ind : indices) {
            result.emplace_back(nodes[ind].terminal);
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

    int count_terminals(int u) {
        int term = nodes[u].terminal;
        for (int v : nodes[u].rsufs) {
            term += count_terminals(v);
        }
        return nodes[u].terminal = term;
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

        vector<int> rsufs;
        int suf_link = - 1;
        int terminal = 0;

        explicit Node(int ch = 0, int parent = -1)
                : next(ALPHABET_SIZE, -1)
                , ch(ch), parent(parent) {}
    };

    vector<int> indices;
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

    for (int c : aut.process(text)) {
        cout << c << endl;
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