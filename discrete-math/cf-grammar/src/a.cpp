#include <bits/stdc++.h>

using namespace std;

vector<map<char, vector<char>>> rules(30);

bool correct(char s, int ind, string word) {
    if (ind == word.length() && s == '\t') {
        return true;
    } else if (s == '\t' || ind >= word.length()) {
        return false;
    }
    bool res = false;
    for (char to : rules[s - 'A'][word[ind]]) {
        res |= correct(to, ind + 1, word);
    }
    return res;
}

void solve() {
    int n, m; char s;
    cin >> n >> s;

    for (string l, _, r; n-- && cin >> l >> _ >> r;) {
        rules[l[0] - 'A'][r[0]].emplace_back(r.length() > 1 ? r[1] : '\t');
    }

    cin >> m;
    for (string str; m-- && cin >> str;) {
        cout << (correct(s, 0, str) ? "yes" : "no") << endl;
    }
}

int main() {
#ifndef LOCAL
    string file = "automaton";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
