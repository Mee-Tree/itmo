#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> rules(30);
set<char> eps = {'\t'};

void check(char s) {
    if (eps.count(s)) return;
    for (auto & v : rules[s - 'A']) {
        bool add = !v.empty();
        for (char ch : v) {
            add &= eps.count(ch);
        }
        if (add) eps.insert(s);
    }
}

void solve() {
    int n; char s;
    cin >> n >> s;
    cin.ignore();

    for (string line; n-- && getline(cin, line);) {
        string r = "\t";
        if (line.length() > 5) {
            r = line.substr(5, line.length());
        }
        rules[line[0] - 'A'].emplace_back(r);
    }

    int sz;
    do {
        sz = eps.size();
        for (char ch = 'A'; ch <= 'Z'; ++ch) check(ch);
    } while (sz != eps.size());

    for (char ch : eps) {
        if (ch == '\t') continue;
        cout << ch << " ";
    }
}

int main() {
#ifndef LOCAL
    string file = "epsilon";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
