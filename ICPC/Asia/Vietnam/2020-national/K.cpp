#include "bits/stdc++.h"
using namespace std;

#define int long long

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator - (const Point& a) const {
        return Point(x-a.x, y-a.y);
    }
    int operator % (const Point& a) const {
        return x*a.y - y*a.x;
    }
};

int ccw(const Point& a, const Point& b, const Point& c) {
    int t = (b - a) % (c - a);
    if (t == 0) return 0;
    if (t < 0) return -1;
    return 1;
}

int32_t main() {
    int n;
    while (cin >> n && n) {
        vector<Point> a(n);
        for (auto & p : a) {
            cin >> p.x >> p.y;
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                for (int k = i+1; k < n; k++) {
                    for (int l = i+1; l < n; l++) {
                        if (ccw(a[i], a[j], a[k]) == 1
                                && ccw(a[j], a[k], a[l]) == 1
                                && ccw(a[k], a[l], a[i]) == 1
                                && ccw(a[l], a[i], a[j]) == 1) {
                            res++;
                        }
                    }
                }
            }
        }
        cout << res << endl;
    }
}
