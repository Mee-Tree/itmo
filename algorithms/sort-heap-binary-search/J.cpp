#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPS = 1e-8;

int Vp, Vf;
double a;

double time(double x) {
    return (sqrt((1 - a) * (1 - a) + x * x) / Vp +
            sqrt((1 - x) * (1 - x) + a * a) / Vf);
}

signed main() {
    cin >> Vp >> Vf >> a;
    double left = 0, right = 1 + EPS;
    while (fabs(left - right) > EPS) {
        double m1 = left + (right - left) / 3;
        double m2 = right + (left - right) / 3;
        if (time(m1) > time(m2)) {
            left = m1;
        } else {
            right = m2;
        }
    }
    cout << fixed << setprecision(8) << (left + right) / 2.0;

    return 0;
}