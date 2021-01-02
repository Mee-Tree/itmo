#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;

void Insert(int val) {
    heap.push_back(val);
    for (int i = (int)heap.size() - 1; heap[i] > heap[(i - 1) / 2]; i = (i - 1) / 2) {
        swap(heap[i], heap[(i - 1) / 2]);
    }
}

int Extract(){
    int maxElement = heap[0];
    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    for (int i = 0; 2 * i + 1 < heap.size();) {
        int son = 2 * i + 1;
        if (son + 1 < heap.size() && heap[son + 1] > heap[son]) {
            son++;
        }
        if (heap[i] >= heap[son]) break;
        swap(heap[i], heap[son]);
        i = son;
    }
    return maxElement;
}

signed main() {
    int q;
    cin >> q;
    while(q--) {
        int cmd;
        cin >> cmd;
        if (cmd) {
            cout << Extract() << "\n";
        } else {
            int value;
            cin >> value;
            Insert(value);
        }
    }

    return 0;
}