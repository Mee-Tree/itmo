#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;
const int SIZE = 'Z' - 'A' + 10;

void solve() {
    int n; char s;
    cin >> n >> s;

    vector<vector<char>> term(SIZE);
    vector<vector<pair<char, char>>> nonterm(SIZE);
    for (string l, _, r; n-- && cin >> l >> _ >> r;) {
        if (r.size() == 1) {
            term[l[0] - 'A'].emplace_back(r[0]);
        } else {
            nonterm[l[0] - 'A'].emplace_back(r[0], r[1]);
        }
    }

    string word;
    cin >> word;
    n = word.size();

    vector<vector<vector<ll>>> dp(SIZE,
            vector<vector<ll>>(n, vector<ll>(n)));
    for (int i = 0; i < n; ++i) {
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            for (char c : term[ch - 'A']) {
                dp[ch - 'A'][i][i] += (c == word[i]);
            }
        }
    }

    for (int m = 1; m < n; ++m) {
        for (int i = 0; i + m < n; ++i) {
            for (int k = i, j = i + m; k < j; ++k) {
                for (char A = 'A'; A <= 'Z'; ++A) {
                    for (auto [B, C] : nonterm[A - 'A']) {
                        dp[A - 'A'][i][j] = (dp[A - 'A'][i][j] + dp[B - 'A'][i][k] * dp[C - 'A'][k + 1][j]) % MOD;
                    }
                }
            }
        }
    }

    cout << dp[s - 'A'][0][n - 1];

}

signed main() {
#ifndef LOCAL
    string file = "nfc";
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
