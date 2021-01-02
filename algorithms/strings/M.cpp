#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,popcnt,abm,mmx,tune=native")
#pragma GCC optimize("fast-math")

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

#define all(x) x.begin(), x.end()

using namespace std;
using ll = long long;

vector<int> suf_array;
vector<int> classes;
int sz;

bool cmp(int i, int j) {
    return tie(classes[i], classes[(i + sz) % classes.size()])
         < tie(classes[j], classes[(j + sz) % classes.size()]);
}

bool neq(int i, int j) {
    return cmp(i, j) || cmp(j, i);
}

void build(size_t size) {
    int log = ceil(log2(size));
    for (sz = 1; sz <= (1 << log); sz <<= 1) {
        sort(all(suf_array), cmp);
        vector<int> new_classes(size);
        for (int i = 1; i < size; ++i) {
            new_classes[suf_array[i]] = new_classes[suf_array[i - 1]]
                    + neq(suf_array[i - 1], suf_array[i]);
        }
        classes.swap(new_classes);
    }
}

void build_suf(const string& str) {
    suf_array.resize(str.size());
    classes.resize(str.size());
    iota(all(suf_array), 0);
    sort(all(suf_array), [&str](int i, int j) { return str[i] < str[j]; });
    transform(all(str), classes.begin(), [](int ch) {
        return ch - 'a';
    });
    build(str.size());
}

vector<int> get_lcp(const string& str) {
    vector<int> pos(str.size()), lcp(str.size());
    for (int i = 0; i < str.size(); ++i) {
        pos[suf_array[i]] = i;
    }

    for (int i = 0, cur = 0; i < str.size(); ++i, cur ? --cur : 0) {
        if (pos[i] == str.size() - 1) {
            cur = 0;
            continue;
        }
        int j = suf_array[pos[i] + 1];
        while (i + cur < str.size() && j + cur < str.size() &&
               str[i + cur] == str[j + cur]) {
             ++cur;
        }
        lcp[pos[i]] = cur;
    }
    return lcp;
}

void solve() {
    string s, t;
    cin >> s >> t;
    string tmp(s + '$' + t + '\0');
    build_suf(tmp);
    const auto& lcp = get_lcp(tmp);

    int ind = -1;
    for (int i = 2; i < suf_array.size() - 1; ++i) {
        if ((suf_array[i] < s.size()) == (suf_array[i + 1] < s.size())) {
            continue;
        }
        if (ind == -1 || lcp[i] > lcp[ind]) {
            ind = i;
        }
    }

    cout << tmp.substr(suf_array[ind], lcp[ind]);
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
    solve();
    return 0;
}