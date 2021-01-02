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

const int INF = 1e9 + 228;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> coins(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> coins[i][j];
        }
    }

    vector<vector<int>> dp(n, vector<int>(m));
    vector<string> path(n, string(m, ' '));
    dp[0][0] = coins[0][0];
    path[0][0] = 'E';
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0] + coins[i][0];
        path[i][0] = 'D';
    }

    for (int i = 1; i < m; ++i) {
        dp[0][i] = dp[0][i - 1] + coins[0][i];
        path[0][i] = 'R';
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (dp[i - 1][j] < dp[i][j - 1]) {
                dp[i][j] = dp[i][j - 1] + coins[i][j];
                path[i][j] = 'R';
            } else {
                dp[i][j] = dp[i - 1][j] + coins[i][j];
                path[i][j] = 'D';
            }

        }
    }
    cout << dp[n - 1][m - 1] << "\n";

    string ans;
    for (int i = n - 1, j = m - 1; path[i][j] != 'E';) {
        ans.push_back(path[i][j]);
        if (path[i][j] == 'R') --j;
        else --i;
    }
    reverse(ans.begin(), ans.end());
    cout << ans;

    return 0;
}