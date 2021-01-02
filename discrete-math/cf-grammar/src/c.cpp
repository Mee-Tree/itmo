#include <bits/stdc++.h>

using namespace std;

const int SIZE = 'Z' - 'A' + 1;

void solve() {
    int n; char s;
    cin >> n >> s;
    cin.ignore();

    set<char> all{s};
    vector<pair<char, string>> rules;
    for (string line; n-- && getline(cin, line);) {
        string r = line.length() > 5 ? line.substr(5) : "";
        rules.emplace_back(line[0], r);
        all.insert(r.begin(), r.end());
        all.insert(line[0]);
    }

    set<char> generatable;
    for (size_t sz = 666; sz != generatable.size();) {
        sz = generatable.size();
        for (auto & [left, right] : rules) {
            if (all_of(right.begin(), right.end(), [&](char ch) {
                return generatable.count(ch) || islower(ch);
            })) generatable.insert(left);
        }
    }

    vector<pair<char, string>> new_rules;
    for (auto & [left, right] : rules) {
        if (any_of(right.begin(), right.end(), [&](char ch) {
            return !generatable.count(ch) && isupper(ch);
        })) continue;
        new_rules.emplace_back(left, right);
    }

    set<char> reachable;
    if (generatable.count(s)) reachable.emplace(s);
    for (size_t sz = 666; sz != reachable.size();) {
        sz = reachable.size();
        for (auto & [left, right] : new_rules) {
            if (!reachable.count(left)) continue;
            copy_if(right.begin(), right.end(),
                    inserter(reachable, reachable.end()), ::isupper);
        }
    }

    for (char ch : all) {
        if (!isupper(ch)) break;
        if (!reachable.count(ch)) {
            cout << ch << " ";
        }
    }
}

int main() {
#ifndef LOCAL
    string file = "useless";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
