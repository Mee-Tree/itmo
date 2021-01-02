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
const int MOD = 1e9;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> matrix(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> matrix[i][j];
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(1 << (n + 1), INF));
    dp[0][0] = 0;
    for (int m = 0; m < (1 << (n + 1)); ++m) {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j) {
                if (!(m & (1 << j)) && dp[i][m] + matrix[i][j] < dp[j][m | (1 << j)]) {
                    dp[j][m | (1 << j)] = dp[i][m] + matrix[i][j];
                }
            }
        }
    }

    int ind = 0, mask = (1 << (n + 1)) - 1;
    cout << dp[ind][mask] << "\n";

    vector<int> ans;
    while (mask) {
        ans.push_back(ind);
        for (int j = 0; j <= n; ++j) {
            if (mask & (1 << ind) && dp[ind][mask] == dp[j][mask - (1 << ind)] + matrix[j][ind]) {
                mask = mask - (1 << ind);
                ind = j;
                break;
            }
        }
    }
    for (int i = (int)ans.size() - 1; i > 0; --i) {
        cout << ans[i] << " ";
    }

    return 0;
}