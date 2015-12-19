#include <bits/stdc++.h>

using namespace std;

const double PI = acos((double) -1.0);

double f(double x) {
    return (x - x*x*x / 3.0) * PI;
}

double vcut(double h) {
    return f(1) - f(h);
}

double scut(double h) {
    return PI * h * (1 - h*h) + 3 * vcut(h);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);  
    cout << (fixed) << setprecision(9);
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);

    double r = 1.0, V = PI * 4.0 / 3.0;
    double h, l;
    double S = 4*PI;

    while (cin >> h >> l) {
        double sina = 1 / l;
        double cosa = sqrt(1.0 - sina*sina);
        double alpha = asin(sina);
        
        double sinb = h;
        double cosb = sqrt(1.0 - sinb*sinb);
        
        if (sinb < sina) cout << 1.0 << endl;
        else {
            double x = cosb * (cosa / sina); 
            double y = x + h;
            double z = (y * y - 1) / x * cosa * cosa;
            double hh = y + 1 - z;
            double res;
            if (hh <= 1) res = scut(1 - hh);
            else res = S - scut(hh - 1);
            cout << res / (S - scut(h)) << endl;
        }
    }
}