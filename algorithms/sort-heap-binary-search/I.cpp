#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-8;

signed main() {
    double c;
    cin >> c;
    double left = 1.0, right = 1e5;
    while (fabs(left - right) > EPS) {
        double mid = left + (right - left) / 2.0;
        if (mid * mid + sqrt(mid) < c) {
            left = mid;
        } else {
            right = mid;
        }
    }
    cout << fixed << setprecision(6) << right;

    return 0;
}