#include <iostream>
#include <vector>

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

class intStack {
private:
    vector<int> st;
public:
    void push(int el) {
        st.push_back(el);
    }
    void pop() {
        st.pop_back();
    }
    int top() {
        return st.back();
    }
    int size() {
        return st.size();
    }
};

class intDeque {
private:
    intStack left;
    intStack right;
public:
    void move(intStack &a, intStack &b) {  //from a to b
        intStack tmp;
        int sz = a.size();
        for (int i = 0; i < sz; ++i) {
            if (i < sz / 2) {
                tmp.push(a.top());
            } else {
                b.push(a.top());
            }
            a.pop();
        }
        while (tmp.size()) {
            a.push(tmp.top());
            tmp.pop();
        }
    }

    void push_front(int el) {
        left.push(el);
    }
    void push_back(int el) {
        right.push(el);
    }

    void pop_front() {
        if (left.size()) {
            left.pop();
            return;
        }
        move(right, left);
        left.pop();
    }
    void pop_back() {
        if (right.size()) {
            right.pop();
            return;
        }
        move(left, right);
        right.pop();
    }

    int front() {
        if (!left.size()) {
            move(right, left);
        }
        return left.top();
    }
    int back() {
        if (!right.size()) {
            move(left, right);
        }
        return right.top();
    }

    int size() {
        return (left.size() + right.size());
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    intDeque left, right;
    int n;
    cin >> n;
    intDeque q;
    int arr[int(1e5 + 1)];
    int cnt = 0;
    while (n--) {
        int cmd, id;
        cin >> cmd;
        if (cmd == 1) {
            cin >> id;
            if (q.size()) {
                arr[id] = arr[q.back()] + 1;
            } else {
                arr[id] = 0;
                cnt = 0;
            }
            q.push_back(id);
        } else if (cmd == 2) {
            q.pop_front();
            cnt++;
        } else if (cmd == 3) {
            q.pop_back();
        } else if (cmd == 4) {
            cin >> id;
            cout << arr[id] - cnt << "\n";
        } else {
            cout << q.front() << "\n";
        }
    }

    return 0;
}