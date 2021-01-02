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

#define int long long

const int INF = 1e9 + 228;
const int MOD = 1e9;

bool match(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

signed main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<vector<pair<string, int>>> dp(n, vector<pair<string, int>>(n));
    for (int i = 0; i < n; ++i) {
        for (int len = 1; len <= n - i; ++len) {
            dp[i][i + len - 1].first = s.substr(i, len);
            dp[i][i + len - 1].second = INF;
        }
    }

    for (int r = 0; r < n; ++r) {
        for (int l = r; l >= 0; --l) {
            if (l == r) {
                dp[l][r].second = 1;
                dp[l][r].first = "";
                continue;
            }

            int mn = INF;
            string cur;
            if (match(s[l], s[r])) {
                mn = dp[l + 1][r - 1].second;
                cur = s[l] + dp[l + 1][r - 1].first + s[r];
            }

            for (int m = l; m < r; ++m) {
                if (dp[l][m].second + dp[m + 1][r].second < mn) {
                    mn = dp[l][m].second + dp[m + 1][r].second;
                    cur = dp[l][m].first + dp[m + 1][r].first;
                }
            }

            if (dp[l][r].second > mn) {
                dp[l][r].second = mn;
                dp[l][r].first = cur;
            }
        }
    }
    cout << dp[0][n - 1].first;

    return 0;
}