#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

double a, v, l, d, w;
#define case1 case1_
bool case1(double &t) {
    // DEBUG(1);
    double tl = sqrt(l * 2 / a);
    if (a * tl > v) return false;

    double td = sqrt(d * 2 / a);
    if (a * td > w) return false;

    t = tl;
    return true;
}

bool case2(double &t) {
    // DEBUG(2);
    double tmax = v / a;
    double dmax = tmax * tmax * a / 2;

    if (dmax >= d) {
        double td = sqrt(d * 2 / a);
        if (a * td > w) return false;

        t = tmax + (l - dmax) / v;
        return true;
    }
    else {
        if (w < v) return false;
        t = tmax + (l - dmax) / v;
        return true;
    }
}

void solve(double &t) {
    double need = l - d;
    double tmax = (v - w) / a;

    if ((v + w) * tmax / 2 > need) {
        double x1 = (-w + sqrt(w*w + 2*a*need)) / a;
        double x2 = (-w - sqrt(w*w + 2*a*need)) / a;

        if (x2 < 0) t += x1;
        else t += x2;
    }
    else {
        t += tmax;
        need -= (w + v) * tmax / 2;

        t += need / v;
    }
}

bool case3(double &t) {
    // DEBUG(3);
    double t1 = sqrt((2*d + w*w / a) / 2 / a);
    double t2 = t1 - w / a;

    if (t1 * a > v) return false;

    t = t1 + t2;
    solve(t);
    return true;
}

void case4(double &t) {
    // DEBUG(4);
    double t0 = v / a;
    double t2 = (v - w) / a;
    double t1 = (d - (a * t0 * t0 / 2) - ((v + w) * t2 / 2)) / v;

    t = t0 + t1 + t2;
    solve(t);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    while (cin >> a >> v >> l >> d >> w) {
        if (w > v) w = v;
        double t;
        if (case1(t)) cout << t << endl;
        else if (case2(t)) cout << t << endl;
        else if (case3(t)) cout << t << endl;
        else {
            case4(t);
            cout << t << endl;
        }
    }
    return 0;
}

