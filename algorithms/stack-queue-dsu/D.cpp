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
    while (n--) {
        char cmd;
        cin >> cmd;
        if (cmd == '+') {
            int id;
            cin >> id;
            right.push_back(id);
            while (right.size() > left.size()) {
                left.push_back(right.front());
                right.pop_front();
            }
        } else if (cmd == '*') {
            int id;
            cin >> id;
            if (left.size() == right.size()) {
                left.push_back(id);
            } else if (left.size() == right.size() + 1) {
                right.push_front(id);
            }
        } else {
            cout << left.front() << "\n";
            left.pop_front();
            while (right.size() > left.size()) {
                left.push_back(right.front());
                right.pop_front();
            }
        }

    }

    return 0;
}