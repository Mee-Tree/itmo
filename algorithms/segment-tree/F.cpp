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
using ll = long long;

const int INF = 1e9 + 228;
const int MOD = 1e9;

class SparseTable {
    vector<vector<int>> st;
    vector<int> log;
public:
    SparseTable(int a, int n) {
        log.resize(n + 1);
        for (int i = 0; i <= n; ++i) {
            if (i == 1) {
                log[i] = 0;
                continue;
            }
            log[i] = log[i / 2] + 1;
        }

        st.assign(n + 1, vector<int> (log[n] + 1));
        for (int j = 0; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                if (j == 0) {
                    st[i][j] = a;
                    a = (23LL * a + 21563) % 16714589;
                    continue;
                }
                st[i][j] = min(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
            }
        }
    }

    int rmq(int l, int r) {
        int j = log[r - l];
        return min(st[l][j], st[r - (1 << j)][j]);
    }
};

signed main() {
    int n, m;
    cin >> n >> m;

    int a, l, r;
    cin >> a >> l >> r;

    SparseTable st(a, n);
    int ans = st.rmq(l - 1, r);
    for (int i = 1; i < m; ++i) {
        l = ((17 * l + 751 + ans + 2LL * i) % n) + 1;
        r = ((13 * r + 593 + ans + 5LL * i) % n) + 1;
        ans = st.rmq(min(l - 1, r - 1), max(l, r));
    }
    cout << l << " " << r << " " << ans << "\n";
    return 0;
}