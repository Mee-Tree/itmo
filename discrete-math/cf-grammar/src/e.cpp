#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int SIZE = 'Z' - 'A' + 10;

void solve() {
    int n; char s;
    cin >> n >> s;
    cin.ignore();

    int ii = 0;
    vector<pair<char, string>> rules;
    for (string line; ii < n && getline(cin, line); ++ii) {
        string r = (line.length() > 5 ? line.substr(5) : "");
        rules.emplace_back(line[0], r);
    }

    string word;
    cin >> word;
    n = word.size();

    vector<vector<vector<bool>>> dp(SIZE,
            vector<vector<bool>>(n + 1, vector<bool>(n + 1)));
    vector<vector<vector<vector<bool>>>> h(51,
           vector<vector<vector<bool>>>(n + 1,
                vector<vector<bool>>(n + 1, vector<bool>(6))));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < rules.size(); ++j) {
            auto & [ch, str] = rules[j];
            dp[ch - 'A'][i][i] = dp[ch - 'A'][i][i] || str.empty();
            if (i < n) {
                dp[ch - 'A'][i][i + 1] = (str.size() == 1 && str[0] == word[i]);
            }
            h[j][i][i][0] = true;
        }
    }

    for (int m = 1; m <= n; ++m) {
        for (int i = 0; i + m <= n; ++i) {
            for (int _ = 0, j = i + m; _ < 10; ++_) {
                for (int ind = 0; ind < rules.size(); ++ind) {
                    auto & [ch, str] = rules[ind];
                    for (int k = 1; k <= str.size(); ++k) {
                        for (int r = i; r <= j; ++r) {
                            if (islower(str[k - 1])) {
                                h[ind][i][j][k] = h[ind][i][j][k] ||
                                        h[ind][i][r][k - 1] && (r == j - 1) && (word[r] == str[k - 1]);
                            } else {
                                h[ind][i][j][k] = h[ind][i][j][k] ||
                                        h[ind][i][r][k - 1] && dp[str[k - 1] - 'A'][r][j];

                            }
                        }
                    }
                }
                for (int ind = 0; ind < rules.size(); ++ind) {
                    auto & [ch, str] = rules[ind];
                    dp[ch - 'A'][i][j] = dp[ch - 'A'][i][j] || h[ind][i][j][str.size()];
                }
            }
        }
    }
    cout << (dp[s - 'A'][0][n] ? "yes" : "no");

}

signed main() {
#ifndef LOCAL
    string file = "cf";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
