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

signed main() {
    int n;
    cin >> n;

    vector<int> price(n);
    for (int i = 0; i < n; ++i) {
        cin >> price[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> prev(n + 1, vector<int>(n + 1));
    dp[0][0] = 0;
    for (int day = 1; day <= n; ++day) {
        for (int coupons = 0; coupons <= n; ++coupons) {
            int p = price[day - 1];
            dp[day][coupons] = dp[day - 1][coupons] + p;
            prev[day][coupons] = coupons;

            if (coupons > 0 && p > 100) {
                if (dp[day - 1][coupons - 1] + p < dp[day][coupons]) {
                    dp[day][coupons] = dp[day - 1][coupons - 1] + p;
                    prev[day][coupons] = coupons - 1;
                }
            }

            if (coupons < n) {
                if (dp[day - 1][coupons + 1] < dp[day][coupons]) {
                    dp[day][coupons] = dp[day - 1][coupons + 1];
                    prev[day][coupons] = coupons + 1;
                }
            }
        }
    }

    int ans = INF;
    int remain = 0;
    for (int i = 0; i <= n; ++i) {
        if (dp[n][i] <= ans) {
            ans = dp[n][i];
            remain = i;
        }
    }
    cout << ans << "\n";
    cout << remain << " ";

    vector<int> used;
    for (int i = n; i > 0; --i) {
        if (prev[i][remain] == remain + 1) {
            used.push_back(i);
        }
        remain = prev[i][remain];
    }

    cout << used.size() << "\n";
    for (int i = (int)used.size() - 1; i >= 0; --i) {
        cout << used[i] << "\n";
    }
    return 0;
}