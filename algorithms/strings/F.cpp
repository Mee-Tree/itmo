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

#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

const int INF = 1e8 + 228;
const ll PRIME = 37;
const ll MOD = 69'420'1337;
ll POW[(int) 1e5 + 1]{0};

void init() {
    POW[0] = 1;
    for (int i = 1; i <= 1e5; ++i) {
        POW[i] = (POW[i - 1] * PRIME) % MOD;
    }
}

vector<string> strings;
vector<vector<ll>> hashes;

ll get_hash(int i, int j, int len) {
    return (MOD * MOD + hashes[i][j + len] - hashes[i][j] * POW[len]) % MOD;
}

string common(int len) {
    unordered_set<int> set;
    for (int i = 0; i + len < hashes.front().size(); ++i) {
        set.insert(get_hash(0, i, len));
    }

    for (int i = 0; i < hashes.size(); ++i) {
        unordered_set<int> new_set;
        for (int j = 0; j + len < hashes[i].size(); ++j) {
            ll hash = get_hash(i, j, len);
            if (!set.count(hash)) { continue; }
            new_set.insert(hash);
            if (i == hashes.size() - 1) {
                return strings[i].substr(j, len);
            }
        }
        set.swap(new_set);
    }
    return "";
}

void solve() {
    int k;
    cin >> k;
    strings.resize(k);
    hashes.resize(k);

    int left = 0, right = INF;
    for (int i = 0; i < k; ++i) {
        cin >> strings[i];
        hashes[i].resize(strings[i].size() + 1);
        right = min(right, (int) hashes[i].size());

        for (int j = 1; j <= strings[i].size(); ++j) {
            hashes[i][j] = (hashes[i][j - 1] * PRIME + (strings[i][j - 1] - 'a' + 1)) % MOD;
        }
    }

    string result;
    while (left + 1 < right) {
        size_t mid = (left + right) / 2;
        const string& str = common(mid);
        if (!str.empty()) {
            result = str;
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << result;
}

signed main() {
#ifdef LOCAL
    const string FILENAME = "local";
    freopen((FILENAME + ".in").c_str(), "r", stdin);
    freopen((FILENAME + ".out").c_str(), "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    solve();
    return 0;
}